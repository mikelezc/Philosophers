/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/11 19:48:14 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ph_usleep(size_t usec)
{
	size_t	start;

	start = ph_what_time_is_it();
	while ((ph_what_time_is_it() - start) < usec)
		usleep(500);
	return (0);
}

size_t	ph_what_time_is_it(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ph_error_exit(ERR_TIME);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
