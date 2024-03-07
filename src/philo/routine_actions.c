#include "../../inc/philo.h"

// Think routine funtion

void	think(t_philo *philo)
{
	ph_peter_says("is thinking", philo, philo->id);
}

// Dream routine funtion

void	dream(t_philo *philo)
{
	ph_peter_says("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

// Eat routine funtion

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	ph_peter_says("has taken a fork", philo, philo->id);
	philo->eating = 1;
	ph_peter_says("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
