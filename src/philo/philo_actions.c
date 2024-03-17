/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:20:50 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/17 15:22:15 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_philo_think(t_diner *diner)
{
	ph_peter_says(diner->id, "is thinking", diner);
}

void	ph_philo_sleep(t_diner *diner)
{
	ph_peter_says(diner->id, "is sleeping", diner);
	ph_sleep(diner->table->t_sleep);
}

bool	ph_check_dinner_finish(t_diner *philo)
{
	pthread_mutex_lock(&philo->table->finish_mtx);
	if (philo->table->finish_flag)
	{
		pthread_mutex_unlock(&philo->table->finish_mtx);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->finish_mtx);
	return (false);
}

void	*ph_philo_actions(void *argmnts)
{
	t_diner	*diner;

	diner = (t_diner *)argmnts;
	if (diner->id % 2 == 0)
		ph_sleep(3);
	while (!ph_check_dinner_finish(diner))
	{
		ph_philo_eat(diner);
		ph_philo_sleep(diner);
		ph_philo_think(diner);
	}
	return (argmnts);
}
