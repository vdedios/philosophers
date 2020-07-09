#include "philo_one.h"

void	*philo_get_forks(t_philo_info *philo)
{
	while (!ask_the_waiter(philo))
		sem_post(philo->general->waiter);
	ft_is_philo_alive(philo);
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, GOT_FORK);
	philo->general->forks -= 2;
	philo->general->pos++;
	sem_post(philo->general->waiter);
	return (NULL);
}

void	*philo_eat(t_philo_info *philo)
{
	gettimeofday(&philo->critical_time, NULL);
	ft_print_philo(philo, EATING);
	usleep(philo->general->time_eat * 1000);
	sem_wait(philo->general->counter);
	philo->times_eaten++;
	philo->general->philos_finished_round++;
	if (philo->general->philos_finished_round == philo->general->n_philos)
	{
		philo->general->round++;
		philo->general->philos_finished_round = 0;
	}
	if (philo->general->round == philo->general->n_eat)
	{
		sem_wait(philo->general->message);
		write(1, "all philos have finished eating ", 32);
		ft_itoa_write(philo->general->round);
		write(1, " rounds.\n", 9);
		sem_post(philo->general->get_out);
	}
	philo->general->forks += 2;
	sem_post(philo->general->counter);
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
