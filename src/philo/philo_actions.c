/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:03:16 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/08 13:13:06 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_philo_think(t_philo *philo)
{
	ph_peter_says("is thinking", philo, philo->id);
}

void	ph_philo_dream(t_philo *philo)
{
	ph_peter_says("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	ph_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	philo->eating = 1;
	ph_peter_says("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*ph_philo_actions(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
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
