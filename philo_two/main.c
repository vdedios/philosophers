#include "philo_two.h"

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
	while (i < env->n_philos)
	{
		philos[i].pos = i;
		philos[i].env = env;
		philos[i].n_meals = 0;
		philos[i].start_time = get_time();
		pthread_create(&philos[i].main_thread, NULL,
			execution, (void *)&philos[i]);
		i++;
	}
	sem_wait(env->s_watchdog);
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
		write(1, "Wrong number of args.\n", 22);
		return (0);
	}
	if (!ft_save_args(argc, argv, env))
	{
		write(1, "Wrong args format.\n", 19);
		return (0);
	}
	run_philos(env);
	return (0);
}
