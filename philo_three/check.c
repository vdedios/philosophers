#include "philo_three.h"

void	*check_meal_limit(void *ptr)
{
	t_env	*env;

	while (1)
	{
		env = ((t_env *)ptr);
		sem_wait(env->s_meal_limit);
		env->philos_finished++;
		if (env->philos_finished == env->n_philos)
		{
			sem_wait(env->s_message);
			ft_print_ended(env);
			sem_post(env->s_watchdog);
			return (NULL);
		}
	}
}

void	check_philo_meals(t_philo *philo)
{
	sem_wait((philo->env)->s_status);
	if (philo->n_meals == philo->env->meal_limit)
	{
		sem_post(philo->env->s_meal_limit);
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
