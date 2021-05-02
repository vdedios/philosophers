#include "philo_one.h"

void	check_philo_meals(t_philo *philo)
{
	pthread_mutex_lock((philo->env)->m_status);
	if (philo->n_meals == philo->env->meal_limit)
	{
		philo->env->philos_finished++;
		philo->n_meals++;
	}
	pthread_mutex_unlock((philo->env)->m_status);
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
			pthread_mutex_lock((philo->env)->m_message);
			ft_print_philo(philo, FINISH);
			pthread_mutex_unlock((philo->env)->m_watchdog);
			return (NULL);
		}
		if ((t_time_ms)(get_time() - philo->start_time)
				> (t_time_ms)philo->env->time_die)
		{
			pthread_mutex_lock((philo->env)->m_message);
			ft_print_philo(philo, DEAD);
			pthread_mutex_unlock((philo->env)->m_watchdog);
			return (NULL);
		}
	}
}
