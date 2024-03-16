/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/16 14:25:21 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	myleaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks_pile;
	t_table			table;

	if (argc == 5 || argc == 6)
	{
		if (ph_error_args(&table, argv)
			|| (ph_set_scenario(&table, &forks_pile)))
			return (1);
		ph_start_dinner(&table);
		ph_clean_table(NULL, &table);
	}
	else
		return (ph_error_exit(ERR_ARG));
	//atexit(myleaks);
	return (0);
}
