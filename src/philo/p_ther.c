/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ther.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:58:36 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/17 15:17:58 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_peter_says(int id, char *msg, t_diner *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->peter_says_mtx);
	time = ph_what_time_is_it() - philo->start_time;
	if (!ph_check_dinner_finish(philo))
		printf("%zu %d %s\n", time, id, msg);
	pthread_mutex_unlock(&philo->table->peter_says_mtx);
}

bool	ph_hasnt_eaten_on_time(t_diner *philo, size_t t_die)
{
	pthread_mutex_lock(&philo->table->eat_mtx);
	if (ph_what_time_is_it() - philo->last_meal >= t_die
		/*&& !(philo->is_eating)*/)
	{
		pthread_mutex_unlock(&philo->table->eat_mtx);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->eat_mtx);
		return (false);
	}
}

bool	ph_smone_hs_died(t_diner *diners_list)
{
	int	i;

	i = -1;
	while (++i < diners_list->table->phil_amnt)
	{
		if (ph_hasnt_eaten_on_time(&diners_list[i], diners_list->table->t_die))
		{
			ph_peter_says(diners_list[i].id, "died", &diners_list[i]);
			pthread_mutex_lock(&diners_list->table->finish_mtx);
			diners_list->table->finish_flag = true;
			pthread_mutex_unlock(&diners_list->table->finish_mtx);
			return (true);
		}
	}
	return (false);
}

bool	ph_finished_meals(t_diner *diners_list)
{
	int	hw_mny_finshd_eating;
	int	i;

	if (diners_list->table->nbr_times_to_eat == -1)
		return (false);
	hw_mny_finshd_eating = 0;
	i = -1;
	while (++i < diners_list->table->phil_amnt)
	{
		pthread_mutex_lock(&diners_list->table->eat_mtx);
		if (diners_list[i].times_has_eaten
			>= diners_list->table->nbr_times_to_eat)
			hw_mny_finshd_eating++;
		pthread_mutex_unlock(&diners_list->table->eat_mtx);
	}
	if (hw_mny_finshd_eating == diners_list->table->phil_amnt)
	{
		pthread_mutex_lock(&diners_list->table->finish_mtx);
		diners_list->table->finish_flag = true;
		pthread_mutex_unlock(&diners_list->table->finish_mtx);
		return (true);
	}
	return (false);
}
/*
Peter (or p_ther) is the p_thread who monitors the status 
of the rest of the philosophers: 
He is THE GREAT PETER also known as "El Lince de Entrevías"
He checks if each philosopher has eaten and is still alive.
*/

void	*ph_p_ther(void *argmnts)
{
	t_diner	*diners_list;

	diners_list = (t_diner *)argmnts;
	while (1)
		if (ph_finished_meals(diners_list) || ph_smone_hs_died(diners_list))
			break ;
	return (argmnts);
}
