#include "philo_one.h"

void	*philo_get_forks(t_philo_info *philo)
{
	//Arreglar tenedores
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_right]);
	ft_print_philo(philo, GOT_FORK);
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_left]);
	ft_print_philo(philo, GOT_FORK);
	return (NULL);
}

void	*philo_eat(t_philo_info *philo)
{
	ft_print_philo(philo, IS_DEAD);
	ft_print_philo(philo, EATING);
	usleep(philo->general->time_eat * 1000);
	gettimeofday(&philo->critical_time, NULL);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_left]);
	return (NULL);
}

void	*philo_sleep(t_philo_info *philo)
{
	long int	t;

	ft_print_philo(philo, SLEEPING);
	usleep(philo->general->time_sleep * 1000);
	return (NULL);
}

void	*philo_think(t_philo_info *philo)
{
	ft_print_philo(philo, THINKING);
	return (NULL);
}
