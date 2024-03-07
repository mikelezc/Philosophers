/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/07 13:33:50 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[DINERS_LIM];
	pthread_mutex_t	forks[DINERS_LIM];

	if (argc == 5 || argc == 6)
	{
		if (ph_error_args(argv))
			return (1);
		ph_set_stage(&program, philos, forks, argv);
		ph_start_dinner(&program, forks);
		ph_clean_table(NULL, &program, forks);
	}
	else
		return (ph_error_exit(ERR_ARG));
	return (0);
}
