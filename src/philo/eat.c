/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:22:25 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/16 19:01:13 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_release_forks(t_diner *diner)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				lf_id;
	int				rf_id;

	left_fork = diner->l_frk_mtx;
	right_fork = diner->r_frk_mtx;
	lf_id = diner->id - 1;
	rf_id = diner->id % diner->table->phil_amnt;
	pthread_mutex_lock(left_fork);
	diner->table->shared_fork[lf_id] = 0;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_lock(right_fork);
	diner->table->shared_fork[rf_id] = 0;
	pthread_mutex_unlock(right_fork);
	diner->owned_frks = 0;
}

void	ph_check_fork(t_diner *diner, pthread_mutex_t	*fork, int fork_place)
{
	pthread_mutex_lock(fork);
	if (diner->table->shared_fork[fork_place] == 0)
	{
		diner->table->shared_fork[fork_place] = 1;
		diner->owned_frks += 1;
		ph_peter_says(diner->id, "has taken a fork", diner);
	}
	pthread_mutex_unlock(fork);
}

void	ph_acquire_forks(t_diner *diner)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				lf_id;
	int				rf_id;

	lf_id = diner->id - 1;
	rf_id = diner->id % diner->table->phil_amnt;
	left_fork = diner->l_frk_mtx;
	right_fork = diner->r_frk_mtx;
	if (diner->id % 2 == 0)
	{
		rf_id = diner->id - 1;
		lf_id = diner->id % diner->table->phil_amnt;
		right_fork = diner->l_frk_mtx;
		left_fork = diner->r_frk_mtx;
	}
	while (diner->owned_frks < 2)
	{
		ph_check_fork(diner, left_fork, lf_id);
		ph_check_fork(diner, right_fork, rf_id);
	}
}

void	ph_philo_eat(t_diner *diner)
{
	ph_acquire_forks(diner);
	pthread_mutex_lock(&diner->table->eat_mtx);
	ph_peter_says(diner->id, "is eating", diner);
	diner->last_meal = ph_what_time_is_it();
	diner->times_has_eaten++;
	pthread_mutex_unlock(&diner->table->eat_mtx);
	ph_sleep(diner->table->t_eat);
	diner->is_eating = false;
	ph_release_forks(diner);
}
