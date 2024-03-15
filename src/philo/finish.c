/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:18:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/15 17:48:07 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_error_exit(char *msg)
{
	while (*msg)
		write(1, msg++, 1);
	return (true);
}

void	ph_clean_table(char *msg, t_table *table)
{
	if (msg)
		ph_error_exit(msg);
	pthread_mutex_destroy(&table->peter_says_mtx);
	pthread_mutex_destroy(&table->eat_mtx);
	pthread_mutex_destroy(&table->finish_mtx);
	free(table->shared_fork);
}
