#include "philo_two.h"

void	kill_all(t_env *env, t_philo *philos)
{
	(void)env;
	free(philos);
}
