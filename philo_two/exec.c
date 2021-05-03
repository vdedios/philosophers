#include "philo_two.h"

void	*eating(t_philo *philo)
{
	if (philo->env->meal_limit < 0 || philo->n_meals <= philo->env->meal_limit)
	{
		sem_wait(philo->env->s_forks);
		sem_wait(philo->env->s_forks);
		sem_wait((philo->env)->s_message);
		philo->n_meals++;
		philo->start_time = get_time();
		ft_print_philo(philo, GOT_FORK);
		ft_print_philo(philo, GOT_FORK);
		ft_print_philo(philo, EATING);
		sem_post((philo->env)->s_message);
		better_usleep(philo->env->time_eat);
		sem_post(philo->env->s_forks);
		sem_post(philo->env->s_forks);
	}
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	sem_wait((philo->env)->s_message);
	ft_print_philo(philo, SLEEPING);
    sem_post((philo->env)->s_message);
	better_usleep(philo->env->time_sleep);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	sem_wait((philo->env)->s_message);
	ft_print_philo(philo, THINKING);
    sem_post((philo->env)->s_message);
	return (NULL);
}

void	*execution(void *ptr)
{
	pthread_create(&((t_philo *)ptr)->status_thread, NULL, check_status, ptr);
	while (1)
	{
		eating((t_philo *)ptr);
		sleeping((t_philo *)ptr);
		thinking((t_philo *)ptr);
	}
	return (NULL);
}
