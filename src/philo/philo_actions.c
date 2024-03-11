/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:03:16 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/11 19:37:21 by mlezcano         ###   ########.fr       */
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
	ph_usleep(diner->t_sleep);
}

void	ph_philo_eat(t_diner *diner)
{
	pthread_mutex_lock(diner->l_fork);
	ph_peter_says(diner->id, "has taken a fork", diner);
	if (diner->phil_amnt == 1)
	{
		ph_usleep(diner->t_die);
		pthread_mutex_unlock(diner->l_fork);
		return ;
	}
	pthread_mutex_lock(diner->r_fork);
	ph_peter_says(diner->id, "has taken a fork", diner);
	diner->is_eating = true;
	ph_peter_says(diner->id, "is eating", diner);
	pthread_mutex_lock(diner->eat_mtx);
	diner->last_meal = ph_what_time_is_it();
	diner->times_has_eaten++;
	pthread_mutex_unlock(diner->eat_mtx);
	ph_usleep(diner->t_eat);
	diner->is_eating = false;
	pthread_mutex_unlock(diner->r_fork);
	pthread_mutex_unlock(diner->l_fork);
}

void	*ph_philo_actions(void *argmnts)
{
	t_diner	*diner;

	diner = (t_diner *)argmnts;
	if (diner->id % 2 == 0)
		ph_usleep(1);
	else
	{
		while (!ph_check_dinner_finish(diner))
		{
			ph_philo_eat(diner);
			ph_philo_sleep(diner);
			ph_philo_think(diner);
		}
	}
	return (argmnts);
}
