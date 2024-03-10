/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 14:26:42 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	myleaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_dinner		philos[DINERS_LIM];
	pthread_mutex_t	forks[DINERS_LIM];
	t_table			table;

	if (argc == 5 || argc == 6)
	{
		if (ph_error_args(&table, argv))
			return (1);
		ph_set_stage(&table, philos, forks);
		ph_start_dinner(&table, forks);
		ph_clean_table(NULL, &table, forks);
	}
	else
		return (ph_error_exit(ERR_ARG));
	//atexit(myleaks);
	return (0);
}
