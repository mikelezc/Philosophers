/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:29:48 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 16:17:10 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_setting_philo(t_dinner *philo, t_table *table)
{
	philo->philo_amnt = table->philo_amnt;
	philo->t_die = table->t_die;
	philo->t_eat = table->t_eat;
	philo->t_sleep = table->t_sleep;
	philo->nbr_times_eat = table->nbr_times_eat;
}

void	ph_philos_take_seat(t_dinner *philos, t_table *table,
pthread_mutex_t *forks)
{
	int	i;

	table->dead_flag = 0;
	table->philos = philos;
	i = -1;
	while (++i < table->philo_amnt)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		ph_setting_philo(&philos[i], table);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].peter_says_mtx = &table->peter_says_mtx;
		philos[i].dead_mtx = &table->dead_mtx;
		philos[i].eat_mtx = &table->eat_mtx;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philo_amnt - 1];
		else
			philos[i].r_fork = &forks[i - 1];
	}
}

void	ph_mutex_init_forks(pthread_mutex_t *forks, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_amnt)
		pthread_mutex_init(&forks[i], NULL);
}

void	ph_mutex_init_table(t_table *table)
{
	pthread_mutex_init(&table->peter_says_mtx, NULL);
	pthread_mutex_init(&table->eat_mtx, NULL);
	pthread_mutex_init(&table->dead_mtx, NULL);
}

void	ph_set_stage(t_table *table, t_dinner *philos,
		pthread_mutex_t *forks)
{
	ph_mutex_init_table(table);
	ph_mutex_init_forks(forks, table);
	ph_philos_take_seat(philos, table, forks);
}
