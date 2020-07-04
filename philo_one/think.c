#include "philo_one.h"

void	*philo_think(t_philo_info philo)
{
	long int	t;

	gettimeofday(&philo.general->current_time, NULL);
	t = ft_get_current_time(philo.general->current_time,
			philo.general->init_time);
	pthread_mutex_lock(&philo.general->message);
	ft_print_philo(t, philo.num_philo, 't');
	pthread_mutex_unlock(&philo.general->message);
	usleep(philo.general->time_die * 1000);
	return (NULL);
}
