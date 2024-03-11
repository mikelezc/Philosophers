/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:18:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/11 11:51:06 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_error(char *msg)
{
	while (*msg)
		write(1, msg++, 1);
}

bool	ph_error_exit(char *msg)
{
	while (*msg)
		write(1, msg++, 1);
	return (true);
}

void	ph_clean_table(char *msg, t_table *table, pthread_mutex_t *forks_pile)
{
	int	i;

	if (msg)
		ph_error_exit(msg);
	pthread_mutex_destroy(&table->peter_says_mtx);
	pthread_mutex_destroy(&table->eat_mtx);
	pthread_mutex_destroy(&table->dead_mtx);
	i = -1;
	while (++i < table->phil_amnt)
		pthread_mutex_destroy(&forks_pile[i]);
}
