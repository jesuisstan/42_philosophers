/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:48:41 by acaren            #+#    #+#             */
/*   Updated: 2021/08/28 06:02:10 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	*routine(void *phil)
{
	t_arguments	*ar;

	ar = ((t_philosopher *)phil)->arguments;
	if ((((t_philosopher *)phil)->order % 2) == 0)
		my_sleep(ar->time_to_eat);
	while (!(ar->dead_flag))
	{
		pthread_mutex_lock(&ar->fork[((t_philosopher *)phil)->fid_left]);
		ph_printer(ar, ((t_philosopher *)phil)->order, "has taken a fork");
		pthread_mutex_lock(&ar->fork[((t_philosopher *)phil)->fid_right]);
		ph_printer(ar, ((t_philosopher *)phil)->order, "has taken a fork");
		pthread_mutex_lock(&(ar->dead_meal_protector));
		ph_printer(ar, ((t_philosopher *)phil)->order, "is eating");
		((t_philosopher *)phil)->last_meal_time = get_timestamp();
		pthread_mutex_unlock(&(ar->dead_meal_protector));
		my_sleep(ar->time_to_eat);
		((t_philosopher *)phil)->eaten_times++;
		pthread_mutex_unlock(&ar->fork[((t_philosopher *)phil)->fid_left]);
		pthread_mutex_unlock(&ar->fork[((t_philosopher *)phil)->fid_right]);
		ph_printer(ar, ((t_philosopher *)phil)->order, "is sleeping");
		my_sleep(ar->time_to_sleep);
		ph_printer(ar, ((t_philosopher *)phil)->order, "is thinking");
	}
	return (NULL);
}

static void	check_if_all_feeded(t_arguments *ar, t_philosopher *phil)
{
	int	i;

	i = 0;
	while (i < ar->nbr_of_philos && phil[i].eaten_times >= ar->must_eat_times)
		i++;
	if (i == ar->nbr_of_philos)
	{
		pthread_mutex_lock(&(ar->writing));
		ar->all_feeded_flag = 1;
		write(STDOUT_FILENO, "All pilosophers have been feeded",
			ft_strlen("All pilosophers have been feeded"));
		write(STDOUT_FILENO, "\n", 1);
		pthread_mutex_unlock(&(ar->writing));
	}
}

static void	left_for_dead(t_arguments *ar, t_philosopher *phil)
{
	int	i;

	while (!(ar->all_feeded_flag))
	{
		i = -1;
		while (++i < ar->nbr_of_philos && !(ar->dead_flag))
		{
			pthread_mutex_lock(&(ar->dead_meal_protector));
			if ((get_timestamp() - phil[i].last_meal_time) > ar->time_to_die)
			{
				pthread_mutex_lock(&(ar->writing));
				printf("%lld\t%d\tdead\n", get_timestamp() - ar->start_timestamp,
					phil[i].order);
				ar->dead_flag = 1;
				pthread_mutex_unlock(&(ar->writing));
			}
			pthread_mutex_unlock(&(ar->dead_meal_protector));
		}
		if (ar->dead_flag)
			break ;
		if (ar->must_eat_times != -1)
			check_if_all_feeded(ar, phil);
	}
}

static int	init_threads(t_arguments *ar)
{
	int	i;

	i = 0;
	while (i < ar->nbr_of_philos)
	{
		ar->phil[i].last_meal_time = get_timestamp();
		if (pthread_create(&ar->phil[i].tid, NULL, &routine, &ar->phil[i]) != 0)
			return (ft_return_nbr(-1,
					"something went wrong while threads creating"));
		pthread_detach(ar->phil[i].tid);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments	*ar;
	int			i;

	if (argc < 5 || argc > 6)
		return (ft_return_nbr(1,
				"something went wrong with arguments amount"));
	ar = (t_arguments *)malloc(sizeof(t_arguments));
	if (!ar)
		return (ft_return_nbr(1, "'t_arguments' memory allocation failed"));
	if (!ph_parse_arguments(argc, argv, ar))
		return (1);
	if (init_threads(ar))
		return (1);
	left_for_dead(ar, ar->phil);
	i = 0;
	while (i < ar->nbr_of_philos)
		pthread_mutex_destroy(&(ar->fork[i++]));
	pthread_mutex_destroy(&(ar->dead_meal_protector));
	pthread_mutex_destroy(&(ar->writing));
	free(ar->fork);
	free(ar->phil);
	free(ar);
	return (0);
}
