/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:22:25 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/20 22:48:58 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_release_forks(t_diner *diner)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				leave_first;
	int				leave_second;

	left_fork = diner->l_frk_mtx;
	right_fork = diner->r_frk_mtx;
	leave_first = diner->id - 1;
	leave_second = diner->id % diner->table->phil_amnt;
	pthread_mutex_lock(left_fork);
	diner->table->shared_fork[leave_first] = 0;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_lock(right_fork);
	diner->table->shared_fork[leave_second] = 0;
	pthread_mutex_unlock(right_fork);
	diner->owned_frks = 0;
}

void	ph_check_fork(t_diner *diner, pthread_mutex_t	*fork, int take)
{
	pthread_mutex_lock(fork);
	if (diner->table->shared_fork[take] == 0)
	{
		diner->table->shared_fork[take] = 1;
		diner->owned_frks += 1;
		ph_peter_says(diner->id, "has taken a fork", diner);
	}
	pthread_mutex_unlock(fork);
}

void	ph_acquire_forks(t_diner *diner)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				take_first;
	int				take_second;

	take_first = diner->id - 1;
	take_second = diner->id % diner->table->phil_amnt;
	first_fork = diner->l_frk_mtx;
	second_fork = diner->r_frk_mtx;
	if (diner->id % 2 == 0)
	{
		take_first = diner->id % diner->table->phil_amnt;
		take_second = diner->id - 1;
		first_fork = diner->r_frk_mtx;
		second_fork = diner->l_frk_mtx;
	}
	while (diner->owned_frks < 2 && !(ph_check_dinner_finish (diner)))
	{
		ph_check_fork(diner, first_fork, take_first);
		ph_check_fork(diner, second_fork, take_second);
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
