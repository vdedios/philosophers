#include "philo_one.h"

void	kill_all(t_philo *philo)
{
	t_env *env;
	int i;

	i = -1;
	env = philo[0].env;
	while (++i < env->n_philos)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].right_fork);
		//liberar tenedores
	}
	pthread_mutex_destroy(env->m_message);
	free (philo);
}

void	organize_forks(t_env *env, t_philo *philo)
{
	pthread_mutex_t	*m_fork;
	int				i;

	i = -1;
	m_fork = malloc(env->n_philos * sizeof(pthread_mutex_t));
	if (!m_fork)
		return ;
	while (++i < env->n_philos)
	{
		if (i == 0)
			philo[i].left_fork = m_fork[env->n_philos - 1];
		else
			philo[i].left_fork = m_fork[i - 1];
		if (i == env->n_philos - 1)
			philo[i].right_fork = m_fork[0];
		else
			philo[i].right_fork = m_fork[i];
		pthread_mutex_init(&m_fork[i], NULL);
	}
}

long int	ft_get_current_time(struct timeval current_time
			, struct timeval init_time)
{
	long int	t;

	t = (current_time.tv_sec - init_time.tv_sec) * 1000
		+ (current_time.tv_usec - init_time.tv_usec) / 1000;
	return (t);
}

void	ft_print_philo(t_philo *philo, int action)
{
	struct timeval	current_time;

	pthread_mutex_lock((philo->env)->m_message);
	gettimeofday(&current_time, NULL);
	ft_itoa_write(ft_get_current_time(current_time, (philo->env)->init_time));
	write(1, " philosopher_", 13);
	ft_itoa_write(philo->pos);
	if (action == GOT_FORK)
		write(1, " has taken a fork\n", 18);
	else if (action == EATING)
		write(1, " is eating\n", 11);
	else if (action == SLEEPING)
		write(1, " is sleeping\n", 13);
	else if (action == THINKING)
		write(1, " is thinking\n", 13);
	pthread_mutex_unlock((philo->env)->m_message);
}

t_time_ms	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((t_time_ms)(current.tv_sec * 1000 + current.tv_usec / 1000));
}

void	better_usleep(t_time_ms time_to_sleep)
{
	t_time_ms	stop;

	stop = get_time() + time_to_sleep;
	while (get_time() < stop)
		usleep (1);
}

void	*eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, GOT_FORK);
	better_usleep(philo->env->time_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (NULL);
}

void	*execution(void *ptr)
{
	while (1)
	{
		eat((t_philo *)ptr);
		//sleep((t_philo *)ptr);
		//think((t_philo *)ptr);
	}
	return (NULL);
}

void	*init_philos(t_env *env)
{
	t_philo	*philo;
	int		i;

	i = 0;
	gettimeofday(&env->init_time, NULL);
	philo = malloc(env->n_philos * sizeof(t_philo));
	if (!philo)
		return (NULL);
	organize_forks(env, philo);
	while (i < env->n_philos)
	{
		philo[i].pos = i;
		philo[i].env = env;
		gettimeofday(&philo[i].start_time, NULL);
		pthread_create(&philo[i].thread, NULL
				, execution, (void *)&philo[i]);
		i++;
	}
	//kill_all(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_env			env;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args :(\n", 24);
		return (0);
	}
	if (!ft_save_args(argc, argv, &env))
	{
		write(1, "wrong args :(\n", 14);
		return (0);
	}
	init_philos(&env);
	return (0);
}
