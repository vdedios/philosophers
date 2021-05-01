#include "philo_one.h"

void			*ft_init_locks_and_variables(t_general_info *general)
{
	int i;

	i = -1;
	if (!(general->lock_fork = malloc(general->n_philos
					* sizeof(pthread_mutex_t))))
		return (NULL);
	if (!(general->forks = malloc(general->n_philos * sizeof(int))))
		return (NULL);
	if (!(general->turns = malloc(general->n_philos * sizeof(int))))
		return (NULL);
	while (++i < general->n_philos)
	{
		pthread_mutex_init(&general->lock_fork[i], NULL);
		general->forks[i] = 1;
		general->turns[i] = -1;
	}
	general->round = 0;
	general->pos = 0;
	pthread_mutex_init(&general->message, NULL);
	pthread_mutex_init(&general->waiter, NULL);
	pthread_mutex_init(&general->counter, NULL);
	pthread_mutex_init(&general->get_out, NULL);
	pthread_mutex_lock(&general->get_out);
	return (general->lock_fork);
}

void			ft_get_forks_position(t_philo_info *philo)
{
	philo->fork_right = philo->num_philo;
	philo->fork_left = (philo->num_philo - 1) >= 0
		? philo->num_philo - 1 : philo->general->n_philos - 1;
}

void			ft_print_philo(t_philo_info *philo, int action)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->general->message);
	gettimeofday(&current_time, NULL);
	ft_itoa_write(ft_get_current_time(current_time, philo->general->init_time));
	write(1, " philosopher_", 13);
	ft_itoa_write(philo->num_philo);
	if (action == GOT_FORK)
		write(1, " has taken a fork\n", 18);
	else if (action == EATING)
		write(1, " is eating\n", 11);
	else if (action == SLEEPING)
		write(1, " is sleeping\n", 13);
	else if (action == THINKING)
		write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&philo->general->message);
}

void			ft_is_philo_alive(t_philo_info *philo)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->general->message);
	gettimeofday(&current_time, NULL);
	if (ft_get_current_time(current_time,
				philo->critical_time) > philo->general->time_die + 1)
	{
		ft_itoa_write(ft_get_current_time(current_time, philo->general->init_time));
		write(1, " philosopher_", 13);
		ft_itoa_write(philo->num_philo);
		write(1, " died\n", 6);
		//pthread_mutex_unlock(&philo->general->get_out);
	}
	else
		pthread_mutex_unlock(&philo->general->message);
}

long int		ft_get_current_time(struct timeval current_time
				, struct timeval init_time)
{
	long int	t;

	t = (current_time.tv_sec - init_time.tv_sec) * 1000
		+ (current_time.tv_usec - init_time.tv_usec) / 1000;
	return (t);
}
