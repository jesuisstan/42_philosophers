/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaren <acaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 21:01:59 by acaren            #+#    #+#             */
/*   Updated: 2021/08/24 16:53:49 by acaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ph_printer(t_arguments *arguments, int phil_order, char *status)
{
	pthread_mutex_lock(&(arguments->writing));
	if (!(arguments->dead_flag) && !(arguments->all_feeded_flag))
	{
		ft_putnbr_fd(get_timestamp() - arguments->start_timestamp,
			STDOUT_FILENO);
		write(STDOUT_FILENO, "\t", 1);
		ft_putnbr_fd(phil_order, STDOUT_FILENO);
		write(STDOUT_FILENO, "\t", 1);
		write(STDOUT_FILENO, status, ft_strlen(status));
		write(STDOUT_FILENO, "\n", 1);
	}
	pthread_mutex_unlock(&(arguments->writing));
	return ;
}
