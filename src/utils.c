/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/02/27 14:14:37 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	*ph_super_malloc(size_t len)
{
	void	*alloc;

	alloc = malloc(len);
	if (NULL == alloc)
		ph_error_exit(ERR_ALLOC);
	return (alloc);
}

int	ph_atoi(const char *str)
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
		nbr = (str++ - '0') + (nbr * 10);
	if (nbr > INT_MAX)
	{
		ph_error_exit(ERR_INT_M);
		return (0);
	}
	return (nbr * sign);
}

int	ph_error_exit(const char *msg)
{
	write(2, &msg, sizeof(msg));
	return (1);
}
