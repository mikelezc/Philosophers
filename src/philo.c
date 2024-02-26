/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:25:11 by mlezcano          #+#    #+#             */
/*   Updated: 2024/02/26 11:45:25 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_arg_content(char *arg)
{
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			return (1);
		arg++;
	}
	return (0);
}

int	ph_args_philter(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		ph_error_exit(ERR_PHI);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		ph_error_exit(ERR_T_DIE);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		ph_error_exit(ERR_T_EAT);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		ph_error_exit(ERR_T_SLP);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		ph_error_exit(ERR_N_EAT);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc == 5 || argc == 6)
	{
		if (ph_args_philter(argv) == 1)
			return (1);
		init_program(&program, philos);
		init_forks(forks, ft_atoi(argv[1]));
		init_philos(philos, &program, forks, argv);
		thread_create(&program, forks);
		destory_all(NULL, &program, forks);
	}
	else
		ph_error_exit(ERR_ARG);
	return (0);
}

