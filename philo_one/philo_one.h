#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define GOT_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEAD 5
# define RUN 6
# define END 7

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

/*
** number_of_philosophers time_to_die time_to_eat time_to_sleep
** [number_of_times_each_philosopher_must_eat]
*/

typedef long long	t_time_ms;

typedef struct		s_env{
	pthread_mutex_t *m_message;
	pthread_mutex_t *m_forks;
	pthread_mutex_t *m_watchdog;
	t_time_ms		init_time;
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
}					t_env;

typedef struct		s_philo{
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_time_ms		start_time;
	pthread_t		main_thread;
	pthread_t		status_thread;
	t_env			*env;
	int				pos;
}					t_philo;

/*
** Initialization functions
*/

void	init_main_mutex(t_env *env);
void	dispense_forks(t_env *env, t_philo *philo);

/*
** Execution functions
*/

void	*eating(t_philo *philo);
void	*sleeping(t_philo *philo);
void	*thinking(t_philo *philo);
void	*check_status(void *ptr);
void	*execution(void *ptr);

/*
** Time functions
*/

t_time_ms	get_time(void);
void		better_usleep(t_time_ms time_to_sleep);

/*
** Utils
*/

int				ft_atoi(const char *str);
void			ft_itoa_write(unsigned long long n);
int				ft_save_args(int argc, char **argv, t_env *info);
void		ft_print_philo(t_philo *philo, int action);

/*
** Cleaning
*/

void	kill_all(t_env *env, t_philo *philos);

#endif
