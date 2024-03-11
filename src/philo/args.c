/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:14:38 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/11 20:25:18 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

bool	ph_is_nbr(char *arg)
{
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			return (true);
		arg++;
	}
	return (false);
}

int	ph_atoi(char *str)
{
	int				sign;
	long long int	nbr;

	sign = 1;
	nbr = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (*str - '0') + (nbr * 10);
		str++;
	}
	if (nbr > INT_MAX)
	{
		ph_error_exit(ERR_INT_M);
		return (0);
	}
	return (nbr * sign);
}

bool	ph_error_args(t_table *table, char **argv)
{
	if (ph_atoi(argv[1]) <= 0 || !(ph_is_nbr(argv[1]))
		|| ph_atoi(argv[1]) > DINERS_LIM)
		return (ph_error_exit(ERR_PHI));
	else
		table->phil_amnt = ph_atoi(argv[1]);
	if (ph_atoi(argv[2]) < TIME_LIM || !(ph_is_nbr(argv[2])))
		return (ph_error_exit(ERR_T_DIE));
	else
		table->t_die = ph_atoi(argv[2]);
	if (ph_atoi(argv[3]) < TIME_LIM || !(ph_is_nbr(argv[3])))
		return (ph_error_exit(ERR_T_EAT));
	else
		table->t_eat = ph_atoi(argv[3]);
	if (ph_atoi(argv[4]) < TIME_LIM || !(ph_is_nbr(argv[4])))
		return (ph_error_exit(ERR_T_SLP));
	else
		table->t_sleep = ph_atoi(argv[4]);
	if (argv[5] && (ph_atoi(argv[5]) < 0 || !(ph_is_nbr(argv[5]))))
		return (ph_error_exit(ERR_N_EAT));
	else if (argv[5])
		table->nbr_times_to_eat = ph_atoi(argv[5]);
	else
		table->nbr_times_to_eat = -1;
	return (false);
}
