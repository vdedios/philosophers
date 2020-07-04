#include "philo_one.h"

void	*philo_get_forks(t_philo_info *philo)
{
	long int	t;

	gettimeofday(&philo->general->current_time, NULL);
	t = ft_get_current_time(philo->general->current_time,
			philo->general->init_time);
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_right]);
	ft_print_philo(t, philo->num_philo, 'f');
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_left]);
	ft_print_philo(t, philo->num_philo, 'f');
	return (NULL);
}
