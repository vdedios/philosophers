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
