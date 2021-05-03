#include "philo_three.h"

static int	create_philo_process(t_philo philo)
{
	int			pid;

	pid = fork();
	if (pid == 0)
		execution(&philo);
	return (pid);
}

void	*run_philos(t_env *env)
{
	t_philo		philo;
	pthread_t	meal_limit;
	int			*pids;
	int			i;

	i = 0;
	env->init_time = get_time();
	pids = malloc(env->n_philos * sizeof(int));
	if (!pids)
		return (NULL);
	init_sems(env);
	while (i < env->n_philos)
	{
		philo.pos = i;
		philo.env = env;
		philo.n_meals = 0;
		philo.start_time = get_time();
		pids[i] = create_philo_process(philo);
		i++;
	}
	pthread_create(&meal_limit, NULL, check_meal_limit, (void *)env);
	sem_wait(env->s_watchdog);
	kill_all(pids, env);
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
