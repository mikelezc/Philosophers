/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:15:27 by mlezcano          #+#    #+#             */
/*   Updated: 2024/02/27 13:36:25 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

//libraries
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//error message macros
# define ERR_ARG	"ERROR: incorrect number of arguments\n"

# define ERR_PHI	"ERROR: incorrect number of philosophers\n"
# define ERR_T_DIE	"ERROR: incorrect time to die\n"
# define ERR_T_EAT	"ERROR: incorrect time to eat\n"
# define ERR_T_SLP	"ERROR: incorrect time to sleep\n"
# define ERR_N_EAT	"ERROR: incorrect nbr of times each philosopher must eat\n"

# define ERR_INT_M	"ERROR: incorrect max int. (limit is 2147483647)"
# define ERR_ALLOC	"ERROR: incorrect memory allocation with malloc"

//limits
# define PHILO_MAX 300
# define INT_MAX __INT_MAX__


//colors
# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"

//structure


//philo(main)
int		ph_is_nbr(char *arg);
int		ph_args_philter(char **argv);

//utils
void	*ph_super_malloc(size_t len);
int		ph_atoi(const char *str);
int		ph_error_exit(const char *msg);

//program

#endif