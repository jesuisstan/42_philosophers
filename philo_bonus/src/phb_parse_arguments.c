/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phb_parse_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: St.Krivtsov <stan.krivtsov@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:51:55 by acaren            #+#    #+#             */
/*   Updated: 2023/05/17 22:06:52 by St.Krivtsov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <fcntl.h>

static long long	ph_atoi(char *argv_str)
{
	unsigned long	nbr;

	nbr = 0;
	while (*argv_str >= '0' && *argv_str <= '9')
	{
		nbr = (nbr * 10) + (int)(*argv_str - '0');
		argv_str++;
		if ((nbr > 9223372036854775807 || (nbr == 922337203685477580
					 && *argv_str > '7')))
			return (-1);
	}
	return (nbr);
}

static int	check_argv_is_correct(char **argv_array)
{
	int	i;
	int	j;

	i = 0;
	while (argv_array[++i] != NULL)
	{
		j = 0;
		while (argv_array[i][j] != '\0')
		{
			if (argv_array[i][j] >= '0' && argv_array[i][j] <= '9')
				j++;
			else
				return (ft_return_nbr(1, "something went wrong with argument"));
		}
	}
	if (ph_atoi(argv_array[1]) == 0)
		return (ft_return_nbr(1, "at least 1 philosopher should be provided"));
	if (ph_atoi(argv_array[2]) == 0)
		return (ft_return_nbr(1, "life is a flash but not that short!"));
	while (i--)
	{
		if (ph_atoi(argv_array[i]) < 0)
			return (ft_return_nbr(1, "overflow"));
	}
	return (0);
}

static int	init_semaphores(t_arguments *ar)
{
	sem_unlink("writing");
	sem_unlink("dead_meal_protector");
	sem_unlink("forks");
	ar->writing = sem_open("writing", O_CREAT, 0644, 1);
	if (ar->writing == SEM_FAILED)
		return (ft_return_nbr(1,
				"something went wrong while opening 'writing' semaphore"));
	ar->dead_meal_protector = sem_open("dead_meal_protector",
			O_CREAT, 0644, 1);
	if (ar->dead_meal_protector == SEM_FAILED)
		return (ft_return_nbr(1,
				"something went wrong while opening 'protector' semaphore"));
	ar->forks = sem_open("forks", O_CREAT, 0644, ar->nbr_of_philos);
	if (ar->forks == SEM_FAILED)
		return (ft_return_nbr(1,
				"something went wrong while opening 'forks' semaphores"));
	return (0);
}

static void	init_philos_specifications(t_arguments *arguments)
{
	int	i;

	arguments->phil = (t_philosopher *)malloc(sizeof(t_philosopher)
			* arguments->nbr_of_philos);
	if (!arguments->phil)
		return ;
	i = 0;
	while (i < arguments->nbr_of_philos)
	{
		arguments->phil[i].arguments = arguments;
		arguments->phil[i].eaten_times = 0;
		arguments->phil[i].order = i + 1;
		arguments->phil[i].last_meal_time = arguments->start_timestamp;
		i++;
	}
}

t_arguments	*ph_parse_arguments(int argc, char **argv, t_arguments *arguments)
{
	if (!check_argv_is_correct(argv))
	{
		arguments->nbr_of_philos = ph_atoi(argv[1]);
		arguments->time_to_die = ph_atoi(argv[2]);
		arguments->time_to_eat = ph_atoi(argv[3]);
		arguments->time_to_sleep = ph_atoi(argv[4]);
		if (argc == 6)
		{
			if (ph_atoi(argv[5]) > 0)
				arguments->must_eat_times = ph_atoi(argv[5]);
			else
				return (ft_return_null("amount of times to eat should be > 0"));
		}
		else
			arguments->must_eat_times = -1;
		arguments->dead_flag = 0;
		arguments->all_feeded_flag = 0;
		arguments->start_timestamp = get_timestamp();
		if (init_semaphores(arguments))
			return (ft_return_null("semaphores initialisation failed"));
		init_philos_specifications(arguments);
		return (arguments);
	}
	else
		return (NULL);
}
