#include "philo_one.h"

void	kill_all(t_env *env, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < env->n_philos)
	{
		pthread_mutex_destroy(&env->m_forks[i]);
	}
	pthread_mutex_destroy(env->m_message);
	pthread_mutex_destroy(env->m_watchdog);
	free (env->m_message);
	free (env->m_watchdog);
	free(env->m_forks);
	free(philos);
}
