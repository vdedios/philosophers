#include "philo_one.h"

void	init_main_mutex(t_env *env)
{
	env->m_message = malloc(sizeof(pthread_mutex_t));
	env->m_watchdog = malloc(sizeof(pthread_mutex_t));
	env->m_status = malloc(sizeof(pthread_mutex_t));
	if (!env->m_message || !env->m_watchdog || !env->m_status)
		return ;
	pthread_mutex_init(env->m_message, NULL);
	pthread_mutex_init(env->m_watchdog, NULL);
	pthread_mutex_init(env->m_status, NULL);
}

void	dispense_forks(t_env *env, t_philo *philo)
{
	int				i;

	i = -1;
	env->m_forks = malloc(env->n_philos * sizeof(pthread_mutex_t));
	if (!env->m_forks)
		return ;
	while (++i < env->n_philos)
	{
		if (i == 0)
			philo[i].left_fork = &env->m_forks[env->n_philos - 1];
		else
			philo[i].left_fork = &env->m_forks[i - 1];
		philo[i].right_fork = &env->m_forks[i];
		pthread_mutex_init(&env->m_forks[i], NULL);
	}
}
