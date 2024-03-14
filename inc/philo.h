/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:47 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/14 18:33:31 by mlezcano         ###   ########.fr       */
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

# define ERR_TIME	"Error in function gettimeofday\n"

# define ERR_MALLOC	"error when trying to allocate memory with malloc\n"

//Limits
# define TIME_LIM 60
# define DINERS_LIM 200
# define INT_MAX __INT_MAX__

typedef struct s_table	t_table;

//Structures
typedef struct s_diner
{
	int				id;
	size_t			start_time;
	pthread_t		thread;
	bool			is_eating;
	int				times_has_eaten;
	size_t			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				forks;
	t_table			*table;
}					t_diner;

typedef struct s_table
{
	char			*shared_fork;
	long			phil_amnt;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				nbr_times_to_eat;
	bool			finish_flag;
	pthread_mutex_t	finish_mtx;
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
void	ph_put_forks(t_diner *diners_list, pthread_mutex_t *forks);
void	ph_diners_take_seat(t_diner *diners_list, t_table *table);
void	ph_mutex_init_table(pthread_mutex_t *forks, t_table *table);
bool	ph_set_scenario(t_table *table, pthread_mutex_t *forks);

//start_dinner
int		ph_start_dinner(t_table *table);

//p_ther (Peter "El Lince de Entrevías")
void	ph_peter_says(int id, char *msg, t_diner *philo);
bool	ph_hasnt_eaten_on_time(t_diner *philo, size_t t_die);
bool	ph_smone_hs_died(t_diner *diners_list);
bool	ph_finished_meals(t_diner *diners_list);
void	*ph_p_ther(void *argmnts);

//philo_actions
void	ph_philo_think(t_diner *philo);
void	ph_philo_sleep(t_diner *philo);
bool	ph_check_dinner_finish(t_diner *philo);
void	*ph_philo_actions(void *argmnts);

/*//eat
void	ph_release_forks(t_diner *diner);
void	ph_check_fork(t_diner *diner, pthread_mutex_t	*fork, int fork_place);
void	ph_acquire_forks(t_diner *diner);
void	ph_philo_eat(t_diner *philo);
*/

//eat
void	ph_release_forks(t_diner *diner, pthread_mutex_t	*left_fork,
			pthread_mutex_t	*right_fork);
void	ph_check_fork(t_diner *diner, pthread_mutex_t	*fork, int fork_place);
void	ph_acquire_forks(t_diner *diner, pthread_mutex_t	*left_fork,
			pthread_mutex_t	*right_fork);
void	ph_philo_eat(t_diner *philo);

//time
int		ph_sleep(size_t msec);
size_t	ph_what_time_is_it(void);

//finish
bool	ph_error_exit(char *msg);
void	ph_clean_table(char *msg, t_table *table);

#endif
