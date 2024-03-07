#include "../../inc/philo.h"

void	ph_clean_table(char *msg, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	if (msg)
		ph_error_exit(msg);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	i = -1;
	while (++i < program->philos[0].num_of_philos)
		pthread_mutex_destroy(&forks[i]);
}
