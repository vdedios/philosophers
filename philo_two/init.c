#include "philo_two.h"

void	init_sems(t_env *env)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_message");
	sem_unlink("sem_status");
	sem_unlink("sem_watchdog");
	env->s_message = sem_open("sem_message", O_CREAT | O_EXCL, 0644, 1);
	env->s_status = sem_open("sem_status", O_CREAT | O_EXCL, 0644, 1);
	env->s_watchdog = sem_open("sem_watchdog", O_CREAT | O_EXCL, 0644, 0);
	env->s_forks = sem_open("sem_forks", O_CREAT | O_EXCL, 0644, env->n_philos);
}
