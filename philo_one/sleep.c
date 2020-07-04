#include "philo_one.h"

void	*philo_sleep(t_philo_info philo)
{
	long int	t;

	gettimeofday(&philo.general->current_time, NULL);
	t = ft_get_current_time(philo.general->current_time,
			philo.general->init_time);
	pthread_mutex_lock(&philo.general->message);
	ft_print_philo(t, philo.num_philo, 's');
	pthread_mutex_unlock(&philo.general->message);
	usleep(philo.general->time_sleep * 1000);
	return (NULL);
}
