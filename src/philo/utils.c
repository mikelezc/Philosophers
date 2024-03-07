/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/07 13:04:57 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

// Improved version of sleep function

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

// Gets the current time in milliseconds

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

bool	ph_error_exit(const char *msg)
{
	while (*msg)
		write(1, msg++, 1);
	return (true);
}
