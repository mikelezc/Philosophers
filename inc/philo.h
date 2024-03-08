/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:15:27 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/08 13:12:00 by mlezcano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//Libraries
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

//Error message macros
# define ERR_ARG	"Incorrect number of arguments!\n"

# define ERR_PHI	"Incorrect number of philosophers!\n"
# define ERR_T_DIE	"Incorrect time to die!\n"
# define ERR_T_EAT	"Incorrect time to eat!\n"
# define ERR_T_SLP	"Incorrect time to sleep!\n"
# define ERR_N_EAT	"Incorrect nbr of times each philosopher must eat!\n"

# define ERR_INT_M	"Maximum limit integer exceeded (limit is 2147483647) -> "
# define ERR_ALLOC	"Error allocating memory with malloc\n"

# define ERR_CRE_T	"Thread creation error\n"
# define ERR_JOI_T	"Thread join error\n"

//Limits
# define TIME_LIM 60
# define DINERS_LIM 200
# define INT_MAX __INT_MAX__

//Structures
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

//philo.c (main)

//args
bool	ph_is_nbr(char *arg);
int		ph_atoi(const char *str);
bool	ph_error_args(char **argv);

//set_stage
void	ph_setting_philo(t_philo *philo, char **argv);
void	ph_take_seat(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **argv);
void	ph_set_stage(t_program *program, t_philo *philos,
			pthread_mutex_t *forks, char **argv);

//start_dinner
bool	ph_are_you_dead(t_philo *philo);
int		ph_start_dinner(t_program *program, pthread_mutex_t *forks);

//p_ther (Peter "El Lince de Entrevías")
void	ph_peter_says(char *str, t_philo *philo, int id);
bool	ph_has_died(t_philo *philo, size_t time_to_die);
bool	ph_are_u_ok(t_philo *philos);
bool	ph_did_u_ate(t_philo *philos);
void	*ph_p_ther(void *pointer);

//philo_actions
void	ph_philo_think(t_philo *philo);
void	ph_philo_dream(t_philo *philo);
void	ph_philo_eat(t_philo *philo);
void	*ph_philo_actions(void *pointer);

//time
int		ft_usleep(size_t microseconds);
size_t	get_current_time(void);

//exit
bool	ph_error_exit(const char *msg);
void	ph_clean_table(char *msg, t_program *program,
			pthread_mutex_t *forks);

#endif
