#include "philo_three.h"

void	kill_all(int *pids, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	free(pids);
}
