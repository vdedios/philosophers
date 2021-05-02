#include "philo_two.h"

void	check_philo_meals(t_philo *philo)
{
	sem_wait((philo->env)->s_status);
	if (philo->n_meals == philo->env->meal_limit)
	{
		philo->env->philos_finished++;
		philo->n_meals++;
	}
	sem_post((philo->env)->s_status);
}

void	*check_status(void *ptr)
{
	t_philo	*philo;

	philo = ((t_philo *)ptr);
	while (1)
	{
		check_philo_meals(philo);
		if (philo->env->philos_finished == philo->env->n_philos)
		{
			sem_wait((philo->env)->s_message);
			ft_print_philo(philo, FINISH);
			sem_post((philo->env)->s_watchdog);
			return (NULL);
		}
		if ((t_time_ms)(get_time() - philo->start_time)
				> (t_time_ms)philo->env->time_die)
		{
			sem_wait((philo->env)->s_message);
			ft_print_philo(philo, DEAD);
			sem_post((philo->env)->s_watchdog);
			return (NULL);
		}
	}
}
