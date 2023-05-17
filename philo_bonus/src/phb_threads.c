/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 05:03:08 by acaren            #+#    #+#             */
/*   Updated: 2021/08/28 05:15:06 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	*check_if_all_feeded(void *philosopher)
{
	t_philosopher	*phil;
	t_arguments		*ar;

	ar = ((t_philosopher *)philosopher)->arguments;
	phil = ((t_philosopher *)philosopher);
	while (ar->all_feeded_flag <= ar->nbr_of_philos)
	{
		if (phil->eaten_times == ar->must_eat_times + 1)
		{
			ar->all_feeded_flag++;
		}
		if (ar->all_feeded_flag == ar->nbr_of_philos)
		{
			sem_wait(ar->writing);
			my_sleep(ar->time_to_eat + 50);
			write(STDOUT_FILENO, "All pilosophers have been feeded",
				ft_strlen("All pilosophers have been feeded"));
			write(STDOUT_FILENO, "\n", 1);
			exit(1);
		}
	}
	return (NULL);
}

static void	*left_for_dead(void *philosopher)
{
	t_philosopher	*phil;
	t_arguments		*ar;

	ar = ((t_philosopher *)philosopher)->arguments;
	phil = ((t_philosopher *)philosopher);
	while (1)
	{
		sem_wait(ar->dead_meal_protector);
		if ((get_timestamp() - phil->last_meal_time) > ar->time_to_die)
		{
			sem_wait(ar->writing);
			printf("%lld\t%d\tdead\n", get_timestamp() - ar->start_timestamp,
				phil->order);
			ar->dead_flag = 1;
			exit(1);
		}
		sem_post(ar->dead_meal_protector);
		if (ar->dead_flag)
			break ;
	}
	return (NULL);
}

void	init_threads(t_philosopher	*phil)
{
	t_arguments		*ar;

	ar = phil->arguments;
	if (pthread_create(&phil->tid_dead, NULL, &left_for_dead, phil) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(phil->tid_dead);
	if (ar->must_eat_times > 0)
	{
		if (pthread_create(&phil->tid_feed, NULL, &check_if_all_feeded,
				phil) != 0)
			exit(EXIT_FAILURE);
		pthread_detach(phil->tid_feed);
	}
}
