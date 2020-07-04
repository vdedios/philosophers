#include "philo_one.h"

void	*philo_eat(t_philo_info *philo)
{
	long int	t;

	gettimeofday(&philo->general->current_time, NULL);
	t = ft_get_current_time(philo->general->current_time,
			philo->general->init_time);
	ft_print_philo(t, philo->num_philo, 'e');
	usleep(philo->general->time_eat * 1000);
	gettimeofday(&philo->critical_time, NULL);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_left]);
	/*
	if (ft_get_current_time(philo->general->current_time,
			philo->critical_time) > philo->general->time_die)
	{
		pthread_mutex_lock(&philo->general->message);
		//guardar para la muerte
		pthread_mutex_unlock(&philo->general->message);
		exit(1);
	}
	*/
	return (NULL);
}
