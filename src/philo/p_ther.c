/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ther.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:36 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 18:28:43 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_peter_says(char *msg, t_diner *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->peter_says_mtx);
	time = ph_what_time_is_it() - philo->start_time;
	if (!ph_are_you_dead(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->peter_says_mtx);
}

bool	ph_has_died(t_diner *philo, size_t t_die)
{
	pthread_mutex_lock(philo->eat_mtx);
	if (ph_what_time_is_it() - philo->last_meal >= t_die
		&& philo->is_eating == 0)
		return (pthread_mutex_unlock(philo->eat_mtx), true);
	pthread_mutex_unlock(philo->eat_mtx);
	return (false);
}

bool	ph_are_u_ok(t_diner *diners_list)
{
	int	i;

	i = 0;
	while (i < diners_list[0].phil_amnt)
	{
		if (ph_has_died(&diners_list[i], diners_list[i].t_die))
		{
			ph_peter_says("died", &diners_list[i], diners_list[i].id);
			pthread_mutex_lock(diners_list[0].dead_mtx);
			*diners_list->is_dead = 1;
			pthread_mutex_unlock(diners_list[0].dead_mtx);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ph_did_u_ate(t_diner *diners_list)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (diners_list[0].nbr_times_eat == -1)
		return (true);
	while (++i < diners_list[0].phil_amnt)
	{
		pthread_mutex_lock(diners_list[i].eat_mtx);
		if (diners_list[i].times_has_eaten >= diners_list[i].nbr_times_eat)
			finished_eating++;
		pthread_mutex_unlock(diners_list[i].eat_mtx);
	}
	if (finished_eating == diners_list[0].phil_amnt)
	{
		pthread_mutex_lock(diners_list[0].dead_mtx);
		*diners_list->is_dead = 1;
		pthread_mutex_unlock(diners_list[0].dead_mtx);
		return (false);
	}
	return (true);
}
/*
Peter (or p_ther) is the p_thread who monitors the status 
of the rest of the philosophers: 
He is THE GREAT PETER also known as "El Lince de Entrevías"
*/

void	*ph_p_ther(void *pointer)
{
	t_diner	*diners_list;

	diners_list = (t_diner *)pointer;
	while (1)
		if (!ph_did_u_ate(diners_list) || !ph_are_u_ok(diners_list))
			break ;
	return (pointer);
}
