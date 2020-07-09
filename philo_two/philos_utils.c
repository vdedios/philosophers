#include "philo_one.h"

void			*init_sems_and_variables(t_general_info *general)
{
	int i;

	i = -1;
	if (!(general->turns = malloc(general->n_philos * sizeof(int))))
		return (NULL);
	while (++i < general->n_philos)
		general->turns[i] = -1;
	general->waiter = sem_open("waiter", O_CREAT);
	general->get_out = sem_open("get_out", O_CREAT);
	general->message = sem_open("message", O_CREAT);
	general->counter = sem_open("counter", O_CREAT);
	sem_wait(general->get_out);
	general->forks = general->n_philos;
	general->round = 0;
	general->pos = 0;
	return (NULL);
}

void			ft_print_philo(t_philo_info *philo, int action)
{
	struct timeval	current_time;

	sem_wait(philo->general->message);
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
	sem_post(philo->general->message);
}

void			ft_is_philo_alive(t_philo_info *philo)
{
	struct timeval	current_time;

	sem_wait(philo->general->message);
	gettimeofday(&current_time, NULL);
	if (ft_get_current_time(current_time,
				philo->critical_time) > philo->general->time_die + 1)
	{
		ft_itoa_write(ft_get_current_time(current_time, philo->general->init_time));
		write(1, " philosopher_", 13);
		ft_itoa_write(philo->num_philo);
		write(1, " died\n", 6);
		sem_post(philo->general->get_out);
	}
	else
		sem_post(philo->general->message);
}

long int		ft_get_current_time(struct timeval current_time
				, struct timeval init_time)
{
	long int	t;

	t = (current_time.tv_sec - init_time.tv_sec) * 1000
		+ (current_time.tv_usec - init_time.tv_usec) / 1000;
	return (t);
}
