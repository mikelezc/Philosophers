/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 17:45:09 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

// Improved version of sleep function

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ph_what_time_is_it();
	while ((ph_what_time_is_it() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	ph_what_time_is_it(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
