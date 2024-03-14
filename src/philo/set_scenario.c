/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scenario.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:33:49 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/13 15:42:41 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_put_forks(t_diner *diners_list, pthread_mutex_t *forks_pile)
{
	int	i;

	i = -1;
	while (++i < diners_list->phil_amnt)
	{
		diners_list[i].r_fork = &forks_pile[i];
		if (i == 0)
			diners_list[i].l_fork = &forks_pile[diners_list[i].phil_amnt - 1];
		else
			diners_list[i].l_fork = &forks_pile[i - 1];
	}
}

void	ph_diners_take_seat(t_diner *diners_list, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->phil_amnt)
	{
		diners_list[i].id = i + 1;
		diners_list[i].start_time = ph_what_time_is_it();
		diners_list[i].phil_amnt = table->phil_amnt;
		diners_list[i].t_die = table->t_die;
		diners_list[i].t_eat = table->t_eat;
		diners_list[i].t_sleep = table->t_sleep;
		diners_list[i].nbr_times_to_eat = table->nbr_times_to_eat;
		diners_list[i].is_eating = false;
		diners_list[i].times_has_eaten = 0;
		diners_list[i].last_meal = ph_what_time_is_it();
		diners_list[i].finish_flag = &table->set_finish_flag;
		diners_list[i].peter_says_mtx = &table->peter_says_mtx;
		diners_list[i].finish_mtx = &table->finish_mtx;
		diners_list[i].eat_mtx = &table->eat_mtx;
		diners_list[i].table = table;
		diners_list[i].forks = 0;
	}
}

void	ph_mutex_init_table(pthread_mutex_t *forks_pile, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->phil_amnt)
		pthread_mutex_init(&forks_pile[i], NULL);
	pthread_mutex_init(&table->peter_says_mtx, NULL);
	pthread_mutex_init(&table->eat_mtx, NULL);
	pthread_mutex_init(&table->finish_mtx, NULL);
}

void	ph_set_scenario(t_table *table,
		pthread_mutex_t *forks_pile)
{
	table->set_finish_flag = false;
	table->shared_fork = malloc(sizeof(char) * table->phil_amnt);
	table->diners_list = malloc(sizeof(t_diner) * table->phil_amnt);
	forks_pile = malloc(sizeof(forks_pile) * table->phil_amnt);
	if (!table->shared_fork || !table->diners_list || !forks_pile)
		ph_error_exit("ADIOS HAMIJOS");
	ph_mutex_init_table(forks_pile, table);
	ph_diners_take_seat(table->diners_list, table);
	ph_put_forks(table->diners_list, forks_pile);
}
