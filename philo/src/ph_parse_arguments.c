/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parse_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:51:55 by acaren            #+#    #+#             */
/*   Updated: 2021/08/24 16:49:22 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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

static int	init_mutex(t_arguments *ar)
{
	int	i;

	ar->fork = malloc(ar->nbr_of_philos * sizeof(pthread_mutex_t));
	if (!ar->fork)
		return (ft_return_nbr(1, "'fork' memory allocation failed"));
	i = 0;
	while (i < ar->nbr_of_philos)
	{
		if (pthread_mutex_init(&(ar->fork[i]), NULL))
		{
			free(ar->fork);
			return (ft_return_nbr(1, "'fork' mutex initialisation failed"));
		}
		i++;
	}
	if (pthread_mutex_init(&(ar->dead_meal_protector), NULL))
		return (ft_return_nbr(1, "'protector' mutex initialisation failed"));
	if (pthread_mutex_init(&(ar->writing), NULL))
		return (ft_return_nbr(1, "'writing' mutex initialisation failed"));
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
		arguments->phil[i].fid_left = i;
		if (i == 0)
		{
			if (arguments->nbr_of_philos > 1)
				arguments->phil[i].fid_right = arguments->nbr_of_philos - 1;
			else
				break ;
		}
		else
			arguments->phil[i].fid_right = i - 1;
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
		if (init_mutex(arguments))
			return (ft_return_null("mutex initialisation failed"));
		init_philos_specifications(arguments);
		return (arguments);
	}
	else
		return (NULL);
}
