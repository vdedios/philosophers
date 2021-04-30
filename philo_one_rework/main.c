#include "philo_one.h"

void	kill_all(t_philo *philo)
{
	t_env *env;
	int i;

	i = -1;
	env = philo[0].env;
	while (++i < env->n_philos)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		//liberar tenedores
	}
	pthread_mutex_destroy(env->m_message);
	free (philo);
}

long int	ft_get_current_time(struct timeval current_time
			, struct timeval init_time)
{
	long int	t;

	t = (current_time.tv_sec - init_time.tv_sec) * 1000
		+ (current_time.tv_usec - init_time.tv_usec) / 1000;
	return (t);
}

t_time_ms	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((t_time_ms)(current.tv_sec * 1000 + current.tv_usec / 1000));
}

void	ft_print_philo(t_philo *philo, int action)
{
	struct timeval	current_time;

	pthread_mutex_lock((philo->env)->m_message);
	//gettimeofday(&current_time, NULL);
	ft_itoa_write(get_time() - (philo->env)->init_time);
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
	else if (action == DEAD)
		write(1, " has died\n", 10);
	pthread_mutex_unlock((philo->env)->m_message);
}

void	better_usleep(t_time_ms time_to_sleep)
{
	t_time_ms	stop;

	stop = get_time() + time_to_sleep;
	while (get_time() < stop)
		usleep (1);
}

void	*eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (get_time() - philo->start_time > philo->env->time_die)
	{
		ft_print_philo(philo, DEAD);
		exit(0);
	}
	philo->start_time = get_time();
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, EATING);
	better_usleep(philo->env->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	ft_print_philo(philo, SLEEPING);
	better_usleep(philo->env->time_sleep);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	ft_print_philo(philo, THINKING);
	return (NULL);
}

void	organize_forks(t_env *env, t_philo *philo)
{
	pthread_mutex_t	*m_fork;
	int				i;

	i = -1;
	m_fork = malloc(env->n_philos * sizeof(pthread_mutex_t));
	env->m_message = malloc(sizeof(pthread_mutex_t));
	env->m_ready = malloc(env->n_philos * sizeof(pthread_mutex_t));
	if (!m_fork || !env->m_message)
		return ;
	while (++i < env->n_philos)
	{
		if (i == 0)
			philo[i].left_fork = &m_fork[env->n_philos - 1];
		else
			philo[i].left_fork = &m_fork[i - 1];
		philo[i].right_fork = &m_fork[i];
		pthread_mutex_init(&m_fork[i], NULL);
	}
	pthread_mutex_init(env->m_message, NULL);
	pthread_mutex_init(env->m_ready, NULL);
}

void	*execution(void *ptr)
{
	pthread_mutex_lock(((t_philo *)ptr)->env->m_ready);
	pthread_mutex_unlock(((t_philo *)ptr)->env->m_ready);
	while (1)
	{
		eating((t_philo *)ptr);
		sleeping((t_philo *)ptr);
		thinking((t_philo *)ptr);
	}
	return (NULL);
}

void	*init_philos(t_env *env)
{
	t_philo	*philo;
	int		i;

	i = 0;
	//gettimeofday(&env->init_time, NULL);
	env->init_time = get_time();
	philo = malloc(env->n_philos * sizeof(t_philo));
	if (!philo)
		return (NULL);
	organize_forks(env, philo);
	pthread_mutex_lock(env->m_ready);
	while (i < env->n_philos)
	{
		philo[i].pos = i;
		philo[i].env = env;
		philo[i].start_time = get_time();
		pthread_create(&philo[i].thread, NULL
				, execution, (void *)&philo[i]);
		i++;
	}
	pthread_mutex_unlock(env->m_ready);
	i = -1;
	while (++i < env->n_philos)
		pthread_join(philo[i].thread, NULL);
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
