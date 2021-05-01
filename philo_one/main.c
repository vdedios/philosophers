#include "philo_one.h"

void	*run_philos(t_env *env)
{
	t_philo		*philos;
	int			i;

	i = 0;
	env->init_time = get_time();
	philos = malloc(env->n_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	dispense_forks(env, philos);
	init_main_mutex(env);
	pthread_mutex_lock(env->m_watchdog);
	while (i < env->n_philos)
	{
		philos[i].pos = i;
		philos[i].env = env;
		philos[i].start_time = get_time();
		pthread_create(&philos[i].main_thread, NULL
				, execution, (void *)&philos[i]);
		i++;
	}
	pthread_mutex_lock(env->m_watchdog);
	kill_all(env, philos);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env			*env;
	int				i;

	i = 0;
	env = malloc(sizeof(t_env));
	if (!env)
		return (0);
	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args :(\n", 24);
		return (0);
	}
	if (!ft_save_args(argc, argv, env))
	{
		write(1, "wrong args :(\n", 14);
		return (0);
	}
	run_philos(env);
	return (0);
}
