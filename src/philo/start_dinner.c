/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_diner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:40:30 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 13:53:35 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_check_dinner_finish(t_diner *philo)
{
	pthread_mutex_lock(philo->finish_mtx);
	if (*philo->finish_flag)
	{
		pthread_mutex_unlock(philo->finish_mtx);
		return (true);
	}
	pthread_mutex_unlock(philo->finish_mtx);
	return (false);
}

int	ph_start_dinner(t_table *table, pthread_mutex_t *forks_pile)
{
	pthread_t	p_ther;
	int			i;

	if (pthread_create(&p_ther, NULL, &ph_p_ther, table->diners_list) != 0)
		ph_clean_table(ERR_CRE_T, table, forks_pile);
	i = -1;
	while (++i < table->phil_amnt)
		if (pthread_create(&table->diners_list[i].thread,
				NULL, &ph_philo_actions, &table->diners_list[i]) != 0)
			ph_clean_table(ERR_CRE_T, table, forks_pile);
	i = -1;
	if (pthread_join(p_ther, NULL) != 0)
		ph_clean_table(ERR_JOI_T, table, forks_pile);
	while (++i < table->phil_amnt)
		if (pthread_join(table->diners_list[i].thread, NULL) != 0)
			ph_clean_table(ERR_JOI_T, table, forks_pile);
	return (0);
}
