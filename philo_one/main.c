#include "philo_one.h"

void	*philo_execution(void *ptr)
{
	t_philo_info philo;

	philo = *(t_philo_info *)ptr;
	while (1)
	{
		philo_get_forks((t_philo_info *)ptr);
		philo_eat((t_philo_info *)ptr);
		philo_sleep(*(t_philo_info *)ptr);
		philo_think(*(t_philo_info *)ptr);
	}
	return (NULL);
}

void	*create_philos(t_general_info *general)
{
	t_philo_info	*philo;
	int				i;

	i = 0;
	gettimeofday(&general->init_time, NULL);
	pthread_mutex_init(&general->message, NULL);
	if (!(philo = malloc(general->n_philos * sizeof(t_philo_info))))
		return (NULL);
	general->lock_fork = ft_initialize_fork_locks(*general);
	while (i < general->n_philos)
	{
		philo[i].num_philo = i;
		philo[i].general = general;
		ft_get_forks_position(&philo[i]);
		gettimeofday(&philo[i].critical_time, NULL);
		pthread_create(&philo[i].thread, NULL
				, philo_execution, (void *)&philo[i]);
		i++;
	}
	pthread_join(philo[0].thread, NULL);
	pthread_mutex_destroy(&general->message);
	//liberar tenedores
	//liberar cerrojos tenedores
	//free(philo);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_general_info	general;
	struct timeval	time;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args :(\n", 24);
		return (0);
	}
	if (!ft_save_args(argc, argv, &general))
	{
		write(1, "wrong args :(\n", 14);
		return (0);
	}
	create_philos(&general);
	return (0);
}
