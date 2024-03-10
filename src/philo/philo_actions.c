/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:03:16 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 18:28:47 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_philo_think(t_diner *philo)
{
	ph_peter_says("is thinking", philo, philo->id);
}

void	ph_philo_dream(t_diner *philo)
{
	ph_peter_says("is sleeping", philo, philo->id);
	ft_usleep(philo->t_sleep);
}

void	ph_philo_eat(t_diner *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	if (philo->phil_amnt == 1)
	{
		ft_usleep(philo->t_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	philo->is_eating = 1;
	ph_peter_says("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat_mtx);
	philo->last_meal = ph_what_time_is_it();
	philo->times_has_eaten++;
	pthread_mutex_unlock(philo->eat_mtx);
	ft_usleep(philo->t_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*ph_philo_actions(void *pointer)
{
	t_diner	*philo;

	philo = (t_diner *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (ph_are_you_dead(philo) == false)
	{
		ph_philo_eat(philo);
		ph_philo_dream(philo);
		ph_philo_think(philo);
	}
	return (pointer);
}
