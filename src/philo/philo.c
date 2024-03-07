/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/07 13:05:06 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_error_args(char **argv)
{
	if (ph_atoi(argv[1]) <= 0 || !(ph_is_nbr(argv[1]))
		|| ph_atoi(argv[1]) > DINERS_LIM)
		return (ph_error_exit(ERR_PHI));
	if (ph_atoi(argv[2]) < TIME_LIM || !(ph_is_nbr(argv[2])))
		return (ph_error_exit(ERR_T_DIE));
	if (ph_atoi(argv[3]) < TIME_LIM || !(ph_is_nbr(argv[3])))
		return (ph_error_exit(ERR_T_EAT));
	if (ph_atoi(argv[4]) < TIME_LIM || !(ph_is_nbr(argv[4])))
		return (ph_error_exit(ERR_T_SLP));
	if (argv[5] && (ph_atoi(argv[5]) < 0 || !(ph_is_nbr(argv[5]))))
		return (ph_error_exit(ERR_N_EAT));
	return (false);
}
/*
ARGUMENTS:
argv[1] number_of_philosophers
argv[2]time_to_die
argv[3]time_to_eat
argv[4]time_to_sleep 
argv[5]number_of_times_each_philosopher_must_eat (optional)
*/

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[DINERS_LIM];
	pthread_mutex_t	forks[DINERS_LIM];

	if (argc == 5 || argc == 6)
	{
		if (ph_error_args(argv))
			return (1);
		ph_set_table(&program, philos, forks, argv);
		ph_action(&program, forks);
		ph_clean_table(NULL, &program, forks);
	}
	else
		return (ph_error_exit(ERR_ARG));
	return (0);
}
