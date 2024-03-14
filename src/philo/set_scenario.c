/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scenario.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:33:49 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/14 16:46:02 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_put_forks(t_diner *diners_list, pthread_mutex_t *forks_pile)
{
	int	i;

	i = -1;
	while (++i < diners_list->table->phil_amnt)
	{
		diners_list[i].r_fork = &forks_pile[i];
		if (i == 0)
			diners_list[i].l_fork
				= &forks_pile[diners_list->table->phil_amnt - 1];
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
		diners_list[i].is_eating = false;
		diners_list[i].times_has_eaten = 0;
		diners_list[i].last_meal = ph_what_time_is_it();
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

bool	ph_set_scenario(t_table *table,
		pthread_mutex_t *forks_pile)
{
	table->shared_fork = malloc(sizeof(char) * table->phil_amnt);
	table->diners_list = malloc(sizeof(t_diner) * table->phil_amnt);
	forks_pile = malloc(sizeof(forks_pile) * table->phil_amnt);
	if (!table->shared_fork || !table->diners_list || !forks_pile)
		return (ph_error_exit(ERR_MALLOC));
	else
	{
		table->finish_flag = false;
		ph_mutex_init_table(forks_pile, table);
		ph_diners_take_seat(table->diners_list, table);
		ph_put_forks(table->diners_list, forks_pile);
		return (false);
	}
}
