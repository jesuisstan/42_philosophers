/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:48:41 by acaren            #+#    #+#             */
/*   Updated: 2021/08/24 16:28:11 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

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
	pthread_mutex_t			*fork;
	pthread_mutex_t			writing;
	pthread_mutex_t			dead_meal_protector;
}	t_arguments;

typedef struct s_philosopher
{
	t_arguments	*arguments;
	pthread_t	tid;
	int			eaten_times;
	long long	last_meal_time;
	int			order;
	int			fid_left;
	int			fid_right;
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

#endif
