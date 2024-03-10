/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ther.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:36 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 13:56:20 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_peter_says(char *msg, t_dinner *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->peter_says_mtx);
	time = get_current_time() - philo->start_time;
	if (!ph_are_you_dead(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->peter_says_mtx);
}

bool	ph_has_died(t_dinner *philo, size_t t_die)
{
	pthread_mutex_lock(philo->eat_mtx);
	if (get_current_time() - philo->last_meal >= t_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->eat_mtx), true);
	pthread_mutex_unlock(philo->eat_mtx);
	return (false);
}

bool	ph_are_u_ok(t_dinner *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_amnt)
	{
		if (ph_has_died(&philos[i], philos[i].t_die))
		{
			ph_peter_says("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_mtx);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_mtx);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ph_did_u_ate(t_dinner *philos)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (philos[0].nbr_times_eat == -1)
		return (true);
	while (++i < philos[0].philo_amnt)
	{
		pthread_mutex_lock(philos[i].eat_mtx);
		if (philos[i].meals_eaten >= philos[i].nbr_times_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].eat_mtx);
	}
	if (finished_eating == philos[0].philo_amnt)
	{
		pthread_mutex_lock(philos[0].dead_mtx);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_mtx);
		return (false);
	}
	return (true);
}

void	*ph_p_ther(void *pointer)
{
	t_dinner	*philos;

	philos = (t_dinner *)pointer;
	while (1)
		if (!ph_did_u_ate(philos) || !ph_are_u_ok(philos))
			break ;
	return (pointer);
}
