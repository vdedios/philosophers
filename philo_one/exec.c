#include "philo_one.h"

void	*eating(t_philo *philo)
{
	if (philo->env->meal_limit < 0 || philo->n_meals <= philo->env->meal_limit)
	{
		if (philo->pos % 2)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		pthread_mutex_lock((philo->env)->m_message);
		philo->n_meals++;
		philo->start_time = get_time();
		ft_print_philo(philo, GOT_FORK);
		ft_print_philo(philo, GOT_FORK);
		ft_print_philo(philo, EATING);
		pthread_mutex_unlock((philo->env)->m_message);
		better_usleep(philo->env->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	pthread_mutex_lock((philo->env)->m_message);
	ft_print_philo(philo, SLEEPING);
	pthread_mutex_unlock((philo->env)->m_message);
	better_usleep(philo->env->time_sleep);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	pthread_mutex_lock((philo->env)->m_message);
	ft_print_philo(philo, THINKING);
	pthread_mutex_unlock((philo->env)->m_message);
	return (NULL);
}

void	*execution(void *ptr)
{
	pthread_create(&((t_philo *)ptr)->status_thread, NULL
			, check_status, ptr);
	while (1)
	{
		eating((t_philo *)ptr);
		sleeping((t_philo *)ptr);
		thinking((t_philo *)ptr);
	}
	return (NULL);
}
