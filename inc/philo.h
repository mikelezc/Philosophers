/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlezcano <mlezcano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:15:27 by mlezcano          #+#    #+#             */
/*   Updated: 2024/03/06 15:39:23 by mlezcano         ###   ########.fr       */
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
# define DINERS_LIM 200 /*by default...*/
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

//Colors
# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"

//Philo(main)
int		ph_is_nbr(char *arg);
int		ph_args_philter(char **argv);
void	ph_destroy_all(char *msg, t_program *program,
			pthread_mutex_t *forks);

//Utils
int		ft_usleep(size_t microseconds);
void	print_message(char *str, t_philo *philo, int id);
size_t	get_current_time(void);
int		ph_atoi(const char *str);
int		ph_error_exit(const char *msg);

//Set table
void	ph_philos_sit(t_philo *philos, t_program *program,
			pthread_mutex_t *forks, char **argv);
void	ph_philo_set(t_philo *philo, char **argv);
void	ph_set_table(t_program *program, t_philo *philos,
			pthread_mutex_t *forks, char **argv);

//Diners
int		dead_loop(t_philo *philo);
void	*philo_routine(void *pointer);
int		ph_action(t_program *program, pthread_mutex_t *forks);

//P_ther
int		check_if_all_ate(t_philo *philos);
int		check_if_dead(t_philo *philos);
int		philosopher_dead(t_philo *philo, size_t time_to_die);
void	*ph_viewer(void *pointer);

// Actions
void	eat(t_philo *philo);
void	dream(t_philo *philo);
void	think(t_philo *philo);

#endif
