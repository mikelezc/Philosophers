/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/02/27 14:17:04 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ph_is_nbr(char *arg)
{
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			return (1);
		arg++;
	}
	return (0);
}
/*
ARGUMENTS:
argv[1] number_of_philosophers
argv[2]time_to_die
argv[3]time_to_eat
argv[4]time_to_sleep 
argv[5]number_of_times_each_philosopher_must_eat (optional)
*/

int	ph_args_philter(char **argv)
{
	if (ph_atoi(argv[1]) <= 0 || !(ph_is_nbr(argv[1]))
		|| ph_atoi(argv[1]) > PHILO_MAX)
		return (ph_error_exit(ERR_PHI));
	if (ph_atoi(argv[2]) <= 0 || !(ph_is_nbr(argv[2])))
		return (ph_error_exit(ERR_T_DIE));
	if (ph_atoi(argv[3]) <= 0 || !(ph_is_nbr(argv[3])))
		return (ph_error_exit(ERR_T_EAT));
	if (ph_atoi(argv[4]) <= 0 || !(ph_is_nbr(argv[4])))
		return (ph_error_exit(ERR_T_SLP));
	if (argv[5] && (ph_atoi(argv[5]) < 0 || !(ph_is_nbr(argv[5]))))
		return (ph_error_exit(ERR_N_EAT));
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc == 5 || argc == 6)
	{
		if (ph_args_philter(argv))
			return (1);
		init_program(&program, philos);
		init_forks(forks, ph_atoi(argv[1]));
		init_philos(philos, &program, forks, argv);
		thread_create(&program, forks);
		destory_all(NULL, &program, forks);
	}
	else
		return (ph_error_exit(ERR_ARG));
	return (0);
}

