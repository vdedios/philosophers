#include "philo_one.h"

void	kill_all(t_env *env, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < env->n_philos)
	{
		pthread_mutex_destroy(&env->m_forks[i]);
	}
	pthread_mutex_destroy(env->m_message);
	pthread_mutex_destroy(env->m_watchdog);
	free (env->m_message);
	free (env->m_watchdog);
	free(env->m_forks);
	free(philos);
}

t_time_ms	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((t_time_ms)(current.tv_sec * 1000 + current.tv_usec / 1000));
}

void	ft_print_philo(t_philo *philo, int action)
{
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
	if (philo->pos % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	pthread_mutex_lock((philo->env)->m_message);
	philo->start_time = get_time();
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, GOT_FORK);
	ft_print_philo(philo, EATING);
	pthread_mutex_unlock((philo->env)->m_message);
	better_usleep(philo->env->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	pthread_mutex_lock((philo->env)->m_message);
	ft_print_philo(philo, SLEEPING);
	pthread_mutex_unlock((philo->env)->m_message);
	better_usleep(philo->env->time_sleep);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	pthread_mutex_lock((philo->env)->m_message);
	ft_print_philo(philo, THINKING);
	pthread_mutex_unlock((philo->env)->m_message);
	return (NULL);
}

void	*check_status(void *ptr)
{
	t_philo *philo;

	philo = ((t_philo *)ptr);
	while (1)
	{
		if ((t_time_ms)(get_time() - philo->start_time)
				> (t_time_ms)philo->env->time_die)
		{
			pthread_mutex_lock((philo->env)->m_message);
			ft_print_philo(philo, DEAD);
			pthread_mutex_unlock((philo->env)->m_watchdog);
			return (NULL);
		}
	}
}

void	*execution(void *ptr)
{
	pthread_create(&((t_philo *)ptr)->status_thread, NULL
			, check_status, ptr);
	while (1)
	{
		eating((t_philo *)ptr);
		sleeping((t_philo *)ptr);
		thinking((t_philo *)ptr);
	}
	return (NULL);
}

void	init_main_mutex(t_env *env)
{
	env->m_message = malloc(sizeof(pthread_mutex_t));
	env->m_watchdog = malloc(sizeof(pthread_mutex_t));
	if (!env->m_message || !env->m_watchdog)
		return ;
	pthread_mutex_init(env->m_message, NULL);
	pthread_mutex_init(env->m_watchdog, NULL);
}

void	dispense_forks(t_env *env, t_philo *philo)
{
	int				i;

	i = -1;
	env->m_forks = malloc(env->n_philos * sizeof(pthread_mutex_t));
	if (!env->m_forks)
		return ;
	while (++i < env->n_philos)
	{
		if (i == 0)
			philo[i].left_fork = &env->m_forks[env->n_philos - 1];
		else
			philo[i].left_fork = &env->m_forks[i - 1];
		philo[i].right_fork = &env->m_forks[i];
		pthread_mutex_init(&env->m_forks[i], NULL);
	}
}

void	*handle_end(void *ptr)
{
	pthread_mutex_lock((pthread_mutex_t *)ptr);
	return (NULL);
}

void	*init_philos(t_env *env)
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
	init_philos(env);
	return (0);
}
