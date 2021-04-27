/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:46:19 by vde-dios          #+#    #+#             */
/*   Updated: 2020/07/09 12:05:26 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define GOT_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DEAD 5

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

typedef struct		s_general_info{
	pthread_mutex_t message;
	pthread_mutex_t waiter;
	pthread_mutex_t counter;
	pthread_mutex_t get_out;
	pthread_mutex_t *lock_fork;
	pthread_t		watchdog;
	struct timeval	init_time;
	int				*forks;
	int				*turns;
	int				pos;
	int				round;
	int				philos_finished_round;

	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
}					t_general_info;

typedef struct		s_philo_info{
	pthread_t		thread;
	t_general_info	*general;
	struct timeval	critical_time;
	int				num_philo;
	int				fork_left;
	int				fork_right;
	int				times_eaten;
}					t_philo_info;

/*
** Utils
*/

int					ft_atoi(const char *str);
void				ft_itoa_write(long int num);
void				ft_print_philo(t_philo_info *philo, int action);
void				ft_is_philo_alive(t_philo_info *philo);
int					ft_save_args(int argc, char **argv, t_general_info *info);
long int			ft_get_current_time(struct timeval current_time
										, struct timeval init_time);
void				*ft_init_locks_and_variables(t_general_info *general);
void				ft_get_forks_position(t_philo_info *philo);
int					have_already_eaten_this_round(t_philo_info *philo);
int					is_your_turn(t_philo_info *philo);
int					ask_the_waiter(t_philo_info *philo);

/*
** Philosophers lifestyle
*/

void				*philo_get_forks(t_philo_info *philo);
void				*philo_eat(t_philo_info *philo);
void				*philo_sleep_and_think(t_philo_info *philo);

#endif
