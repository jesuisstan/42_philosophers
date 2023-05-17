/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:48:41 by acaren            #+#    #+#             */
/*   Updated: 2021/08/28 05:04:54 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_arguments
{
	struct s_philosopher	*phil;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				start_timestamp;
	int						nbr_of_philos;
	int						must_eat_times;
	int						dead_flag;
	int						all_feeded_flag;
	sem_t					*forks;
	sem_t					*writing;
	sem_t					*dead_meal_protector;
}	t_arguments;

typedef struct s_philosopher
{
	t_arguments	*arguments;
	pid_t		pid;
	int			eaten_times;
	long long	last_meal_time;
	int			order;
	int			fid_left;
	int			fid_right;
	pthread_t	tid_dead;
	pthread_t	tid_feed;
}	t_philosopher;

t_arguments	*ph_parse_arguments(int argc, char **argv, t_arguments *arguments);
long long	get_timestamp(void);
void		ph_printer(t_arguments *arguments, int phil_order, char *status);
long long	get_timestamp(void);
void		my_sleep(long long timer);
size_t		ft_strlen(char *str);
void		ft_putnbr_fd(long long n, int fd);
void		*ft_return_null(char *message);
int			ft_return_nbr(int return_value, char *message);
void		init_threads(t_philosopher	*phil);

#endif
