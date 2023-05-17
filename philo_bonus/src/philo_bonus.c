/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: St.Krivtsov <stan.krivtsov@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:48:41 by acaren            #+#    #+#             */
/*   Updated: 2023/05/17 22:05:06 by St.Krivtsov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <sys/wait.h>

static void	plilosopher_eats(t_philosopher	*philosopher)
{
	t_arguments		*ar;
	t_philosopher	*phil;

	ar = ((t_philosopher *)philosopher)->arguments;
	phil = ((t_philosopher *)philosopher);
	sem_wait(ar->forks);
	ph_printer(ar, phil->order, "has taken a fork");
	sem_wait(ar->forks);
	ph_printer(ar, phil->order, "has taken a fork");
	sem_wait(ar->dead_meal_protector);
	ph_printer(ar, phil->order, "is eating");
	phil->last_meal_time = get_timestamp();
	sem_post(ar->dead_meal_protector);
	my_sleep(ar->time_to_eat);
	sem_post(ar->forks);
	sem_post(ar->forks);
	phil->eaten_times++;
}

static void	routine(void *philosopher)
{
	t_arguments		*ar;
	t_philosopher	*phil;

	ar = ((t_philosopher *)philosopher)->arguments;
	phil = ((t_philosopher *)philosopher);
	init_threads(phil);
	if ((phil->order % 2) == 0)
		my_sleep(ar->time_to_eat);
	while (!(ar->dead_flag))
	{
		plilosopher_eats(phil);
		ph_printer(ar, phil->order, "is sleeping");
		my_sleep(ar->time_to_sleep);
		ph_printer(ar, phil->order, "is thinking");
	}
	if (ar->dead_flag)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	exit_processes(t_arguments *ar)
{
	int	i;
	int	ret;

	i = 0;
	while (i < ar->nbr_of_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = 0;
			while (i < ar->nbr_of_philos)
			{
				kill(ar->phil[i].pid, SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(ar->forks);
	sem_close(ar->writing);
	sem_close(ar->dead_meal_protector);
	sem_unlink("writing");
	sem_unlink("dead_meal_protector");
	sem_unlink("forks");
}

static int	init_processes(t_arguments *ar)
{
	int				i;
	t_philosopher	*philo;

	philo = ar->phil;
	i = 0;
	while (i < ar->nbr_of_philos)
	{
		philo[i].last_meal_time = get_timestamp();
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (ft_return_nbr(-1,
					"something went wrong while processes creating"));
		if (philo[i].pid == 0)
			routine(&(philo[i]));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments	*ar;

	if (argc < 5 || argc > 6)
		return (ft_return_nbr(1,
				"something went wrong with arguments amount"));
	ar = (t_arguments *)malloc(sizeof(t_arguments));
	if (!ar)
		return (ft_return_nbr(1, "'t_arguments' memory allocation failed"));
	if (!ph_parse_arguments(argc, argv, ar))
		return (1);
	if (init_processes(ar))
		return (1);
	exit_processes(ar);
	return (0);
}
