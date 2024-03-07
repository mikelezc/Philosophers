/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:40:30 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/07 13:40:38 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_are_you_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

// Thread routine

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (ph_are_you_dead(philo) == false)
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	ph_start_dinner(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	p_ther;
	int			i;

	if (pthread_create(&p_ther, NULL, &ph_p_ther, program->philos) != 0)
		ph_clean_table(ERR_CRE_T, program, forks);
	i = -1;
	while (++i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			ph_clean_table(ERR_CRE_T, program, forks);
	}
	i = -1;
	if (pthread_join(p_ther, NULL) != 0)
		ph_clean_table(ERR_JOI_T, program, forks);
	while (++i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			ph_clean_table(ERR_JOI_T, program, forks);
	}
	return (0);
}
