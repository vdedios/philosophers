#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# define GOT_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEAD 5
# define FINISH 6

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

/*
** number_of_philosophers time_to_die time_to_eat time_to_sleep
** [number_of_times_each_philosopher_must_eat]
*/

typedef long long	t_time_ms;

typedef struct s_env{
	sem_t			*s_message;
	sem_t			*s_watchdog;
	sem_t			*s_status;
	sem_t			*s_forks;
	sem_t			*s_meal_limit;
	t_time_ms		init_time;
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal_limit;
	int				philos_finished;
}					t_env;

typedef struct s_philo{
	t_time_ms		start_time;
	pthread_t		status_thread;
	t_env			*env;
	int				pos;
	int				n_meals;
}					t_philo;

/*
** Initialization functions
*/

void				init_sems(t_env *env);

/*
** Status check functions
*/

void				*check_status(void *ptr);
void				*check_meal_limit(void *ptr);
void				check_philo_meals(t_philo *philo);

/*
** Execution functions
*/

void				*eating(t_philo *philo);
void				*sleeping(t_philo *philo);
void				*thinking(t_philo *philo);
void				*execution(t_philo *philo);

/*
** Time functions
*/

t_time_ms			get_time(void);
void				better_usleep(t_time_ms time_to_sleep);

/*
** Utils
*/

int					ft_atoi(const char *str);
void				ft_itoa_write(unsigned long long n);
int					ft_save_args(int argc, char **argv, t_env *info);
void				ft_print_philo(t_philo *philo, int action);
void				ft_print_ended(t_env *env);

/*
** Cleaning
*/

void				kill_all(int *pids, t_env *env);

#endif
