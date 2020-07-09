#include "philo_one.h"

void	*death_watchdog(void *ptr)
{	
	t_general_info *general;

	general = (t_general_info *)ptr;
	pthread_mutex_lock(&general->get_out);
	return (NULL);
}

void	*philo_execution(void *ptr)
{
	while (1)
	{
		philo_get_forks((t_philo_info *)ptr);
		philo_eat((t_philo_info *)ptr);
		philo_sleep_and_think((t_philo_info *)ptr);
	}
	return (NULL);
}

void	kill_all(t_philo_info *philo)
{
	t_general_info *general;
	int i;

	i = -1;
	general = philo[0].general;
	while (++i < general->n_philos)
		pthread_mutex_destroy(&general->lock_fork[i]);
	pthread_mutex_destroy(&general->message);
	pthread_mutex_destroy(&general->waiter);
	pthread_mutex_destroy(&general->counter);
	pthread_mutex_destroy(&general->get_out);
	free (general->lock_fork);
	free (general->forks);
	free (general->turns);
	free (philo);
}

void	*create_philos(t_general_info *general)
{
	t_philo_info	*philo;
	int				i;

	i = 0;
	gettimeofday(&general->init_time, NULL);
	if (!ft_init_locks_and_variables(general))
		return (NULL);
	if (!(philo = malloc(general->n_philos * sizeof(t_philo_info))))
		return (NULL);
	pthread_create(&general->watchdog, NULL
			, death_watchdog, (void *)general);
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
	pthread_join(general->watchdog, NULL);
	kill_all(philo);
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
