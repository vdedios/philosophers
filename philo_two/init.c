#include "philo_two.h"

void	init_main_mutex(t_env *env)
{
	env->s_message = sem_open("s_message", O_CREAT, O_RDWR, 1);
	env->s_watchdog = sem_open("s_watchdog", O_CREAT, O_RDWR, 0);
	env->s_status = sem_open("s_status", O_CREAT, O_RDWR, 1);
}

void	dispense_forks(t_env *env, t_philo *philo)
{
	char			*fork_id;
	int				i;

	env->s_forks = malloc(env->n_philos * sizeof(sem_t *));
	fork_id = malloc(2 * sizeof(char));
	if (!env->s_forks || !fork_id)
		return ;
	fork_id[0] = 41;
	fork_id[1] = '\0';
	i = -1;
	while (++i < env->n_philos)
	{
		env->s_forks[i] = sem_open(fork_id, O_CREAT, O_RDWR, 1);
		fork_id[0]++;
		//probar con sem_unlink
		if (i == 0)
			philo[i].left_fork = env->s_forks[env->n_philos - 1];
		else
			philo[i].left_fork = env->s_forks[i - 1];
		philo[i].right_fork = env->s_forks[i];
	}
	free (fork_id);
}
