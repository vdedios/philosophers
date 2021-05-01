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
** Utils
*/

int				ft_atoi(const char *str);
//static long int	ft_size_num(long int n);
void			ft_itoa_write(unsigned long long n);
int				ft_save_args(int argc, char **argv, t_env *info);

#endif
