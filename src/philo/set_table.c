/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:23:27 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/06 15:24:31 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ph_philo_set(t_philo *philo, char **argv)
{
	philo->time_to_die = ph_atoi(argv[2]);
	philo->time_to_eat = ph_atoi(argv[3]);
	philo->time_to_sleep = ph_atoi(argv[4]);
	philo->num_of_philos = ph_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ph_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	ph_philos_sit(t_philo *philos, t_program *program,
pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ph_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		ph_philo_set(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
	}
}

void	ph_set_table(t_program *program, t_philo *philos,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = -1;
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	while (++i < ph_atoi(argv[1]))
		pthread_mutex_init(&forks[i], NULL);
	ph_philos_sit(philos, program, forks, argv);
}
