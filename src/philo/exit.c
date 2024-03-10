/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:18:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 13:56:12 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_error_exit(char *msg)
{
	while (*msg)
		write(1, msg++, 1);
	return (true);
}

void	ph_clean_table(char *msg, t_table *table, pthread_mutex_t *forks)
{
	int	i;

	if (msg)
		ph_error_exit(msg);
	pthread_mutex_destroy(&table->peter_says_mtx);
	pthread_mutex_destroy(&table->eat_mtx);
	pthread_mutex_destroy(&table->dead_mtx);
	i = -1;
	while (++i < table->philos[0].philo_amnt)
		pthread_mutex_destroy(&forks[i]);
}
