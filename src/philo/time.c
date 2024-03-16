/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:19:34 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/16 19:07:35 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	ph_sleep(size_t msec)
{
	size_t	entry_time;

	entry_time = ph_what_time_is_it();
	while ((ph_what_time_is_it() - entry_time) < msec)
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
