/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scenario.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:29:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 18:12:40 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_distribute_forks(t_diner *diners_list, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < diners_list->philo_amnt)
	{
		diners_list[i].right_fork = &forks[i];
		if (i == 0)
			diners_list[i].left_fork = &forks[diners_list[i].philo_amnt - 1];
		else
			diners_list[i].left_fork = &forks[i - 1];
	}
}

void	ph_diners_take_seat(t_diner *diners_list, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amnt)
	{
		diners_list[i].id = i + 1;
		diners_list[i].start_time = ph_what_time_is_it();
		diners_list[i].philo_amnt = table->philo_amnt;
		diners_list[i].t_die = table->t_die;
		diners_list[i].t_eat = table->t_eat;
		diners_list[i].t_sleep = table->t_sleep;
		diners_list[i].nbr_times_eat = table->nbr_times_eat;
		diners_list[i].is_eating = 0;
		diners_list[i].times_has_eaten = 0;
		diners_list[i].last_meal = ph_what_time_is_it();
		diners_list[i].is_dead = &table->set_deaths;
		diners_list[i].peter_says_mtx = &table->peter_says_mtx;
		diners_list[i].dead_mtx = &table->dead_mtx;
		diners_list[i].eat_mtx = &table->eat_mtx;
	}
}

void	ph_mutex_init_table(pthread_mutex_t *forks, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amnt)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&table->peter_says_mtx, NULL);
	pthread_mutex_init(&table->eat_mtx, NULL);
	pthread_mutex_init(&table->dead_mtx, NULL);
}

void	ph_set_scenario(t_table *table, t_diner *diners_list,
		pthread_mutex_t *forks)
{
	table->set_deaths = 0;
	table->diners_list = diners_list;
	ph_mutex_init_table(forks, table);
	ph_diners_take_seat(diners_list, table);
	ph_distribute_forks(diners_list, forks);
}
