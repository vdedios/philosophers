#include "philo_one.h"

int		have_already_eaten_this_round(t_philo_info *philo)
{
	if (philo->times_eaten <= philo->general->round)
		return (0);
	return (1);
}

int		is_your_turn(t_philo_info *philo)
{
	if (philo->general->pos == philo->general->n_philos)
		philo->general->pos = 0;
	if (philo->general->turns[philo->general->pos] == -1)
		philo->general->turns[philo->general->pos] = philo->num_philo;
	if (philo->general->turns[philo->general->pos] == philo->num_philo)
		return (1);
	return (0);
}

int		ask_the_waiter(t_philo_info *philo)
{
	pthread_mutex_lock(&philo->general->waiter);
	if (philo->general->forks[philo->fork_right]
		&& philo->general->forks[philo->fork_left])
		if (!have_already_eaten_this_round(philo)
			&& is_your_turn(philo))
			return (1);
	return (0);
}

void	*philo_get_forks(t_philo_info *philo)
{
	while (!ask_the_waiter(philo))
		pthread_mutex_unlock(&philo->general->waiter);
	ft_is_philo_alive(philo);
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_left]);
	ft_print_philo(philo, GOT_FORK);
	philo->general->forks[philo->fork_left] = 0;
	pthread_mutex_lock(&philo->general->lock_fork[philo->fork_right]);
	ft_print_philo(philo, GOT_FORK);
	philo->general->forks[philo->fork_right] = 0;
	philo->general->pos++;
	pthread_mutex_unlock(&philo->general->waiter);
	return (NULL);
}

void	*philo_eat(t_philo_info *philo)
{
	gettimeofday(&philo->critical_time, NULL);
	ft_print_philo(philo, EATING);
	usleep(philo->general->time_eat * 1000);
	pthread_mutex_lock(&philo->general->counter);
	philo->times_eaten++;
	philo->general->philos_finished_round++;
	if (philo->general->philos_finished_round == philo->general->n_philos)
	{
		philo->general->round++;
		philo->general->philos_finished_round = 0;
		pthread_mutex_lock(&philo->general->message);
		printf("------ROUND COMPLETED: %d--------\n", philo->general->round);
		pthread_mutex_unlock(&philo->general->message);
	}
	if (philo->general->round == philo->general->n_eat)
	{
		pthread_mutex_lock(&philo->general->message);
		write(1, "all philos have finished eating.", 32);
		exit(1);
	}
	philo->general->forks[philo->fork_right] = 1;
	philo->general->forks[philo->fork_left] = 1;
	pthread_mutex_unlock(&philo->general->counter);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->general->lock_fork[philo->fork_right]);
	return (NULL);
}

void	*philo_sleep_and_think(t_philo_info *philo)
{
	long int	t;

	ft_print_philo(philo, SLEEPING);
	usleep(philo->general->time_sleep * 1000);
	ft_print_philo(philo, THINKING);
	return (NULL);
}
