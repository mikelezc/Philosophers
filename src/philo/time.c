/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/12 21:24:20 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ph_sleep(size_t msec) //TODO
{
	size_t	zero_t;

	zero_t = ph_what_time_is_it();
	while ((ph_what_time_is_it() - zero_t) < msec)
		usleep(500);
	return (0);
}

size_t	ph_what_time_is_it(void)
{
	struct timeval	time;
	size_t			msec;

	if (gettimeofday(&time, NULL) == -1)
		ph_error_exit(ERR_TIME);
	msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (msec);
}
