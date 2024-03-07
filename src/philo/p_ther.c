/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ther.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:36 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/07 13:58:50 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_peter_says(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!ph_are_you_dead(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

bool	ph_has_died(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool	ph_are_u_ok(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (ph_has_died(&philos[i], philos[i].time_to_die))
		{
			ph_peter_says("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ph_did_u_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (true);
	while (++i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (false);
	}
	return (true);
}

void	*ph_p_ther(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (!ph_did_u_ate(philos) || !ph_are_u_ok(philos))
			break ;
	return (pointer);
}
