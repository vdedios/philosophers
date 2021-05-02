#include "philo_two.h"

void	kill_all(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < env->n_philos)
	{
		sem_close(env->s_forks[i]);
	}
	sem_close(env->s_message);
	sem_close(env->s_watchdog);
	sem_close(env->s_status);
	free(env->s_forks);
	free(philos);
}
