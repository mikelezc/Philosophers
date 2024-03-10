/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:15:27 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/10 18:12:44 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Libraries
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

//Error message macros
# define ERR_ARG	"Incorrect number of arguments!\n"

# define ERR_PHI	"Incorrect number of philosophers!\n"
# define ERR_T_DIE	"Incorrect time to die!\n"
# define ERR_T_EAT	"Incorrect time to eat!\n"
# define ERR_T_SLP	"Incorrect time to sleep!\n"
# define ERR_N_EAT	"Incorrect number of times each philosopher must eat!\n"

# define ERR_INT_M	"Maximum limit integer exceeded (limit is 2147483647) -> "
# define ERR_ALLOC	"Error allocating memory with malloc\n"

# define ERR_CRE_T	"Thread creation error\n"
# define ERR_JOI_T	"Thread join error\n"

//Limits
# define TIME_LIM 60
# define DINERS_LIM 200
# define INT_MAX __INT_MAX__

//Structures
typedef struct s_diner
{
	int				id;
	size_t			start_time;
	int				philo_amnt;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				nbr_times_eat;
	pthread_t		thread;
	int				is_eating;
	int				times_has_eaten;
	size_t			last_meal;
	int				*is_dead;
	pthread_mutex_t	*peter_says_mtx;
	pthread_mutex_t	*dead_mtx;
	pthread_mutex_t	*eat_mtx;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_diner;
typedef struct s_table
{
	int				philo_amnt;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				nbr_times_eat;
	int				set_deaths;
	pthread_mutex_t	dead_mtx;
	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	peter_says_mtx;
	t_diner			*diners_list;
}					t_table;

//philo.c (main)

//args
bool	ph_is_nbr(char *arg);
int		ph_atoi(char *str);
bool	ph_error_args(t_table *table, char **argv);

//set_scenario
void	ph_distribute_forks(t_diner *diners_list, pthread_mutex_t *forks);
void	ph_diners_take_seat(t_diner *diners_list, t_table *table);
void	ph_mutex_init_table(pthread_mutex_t *forks, t_table *table);
void	ph_set_scenario(t_table *table, t_diner *diners_list,
			pthread_mutex_t *forks);

//start_dinner
bool	ph_are_you_dead(t_diner *philo);
int		ph_start_dinner(t_table *table, pthread_mutex_t *forks);

//p_ther (Peter "El Lince de Entrevías")
void	ph_peter_says(char *str, t_diner *philo, int id);
bool	ph_has_died(t_diner *philo, size_t t_die);
bool	ph_are_u_ok(t_diner *diners_list);
bool	ph_did_u_ate(t_diner *diners_list);
void	*ph_p_ther(void *pointer);

//philo_actions
void	ph_philo_think(t_diner *philo);
void	ph_philo_dream(t_diner *philo);
void	ph_philo_eat(t_diner *philo);
void	*ph_philo_actions(void *pointer);

//time
int		ft_usleep(size_t microseconds);
size_t	ph_what_time_is_it(void);

//exit
bool	ph_error_exit(char *msg);
void	ph_clean_table(char *msg, t_table *table,
			pthread_mutex_t *forks);

#endif
