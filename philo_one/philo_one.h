/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:46:19 by vde-dios          #+#    #+#             */
/*   Updated: 2020/07/04 22:19:44 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

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
	pthread_mutex_t *lock_fork;
	struct timeval	current_time;
	struct timeval	init_time;
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
}					t_general_info;

typedef struct		s_philo_info{
	t_general_info	*general;
	pthread_t		thread;
	struct timeval	critical_time;
	int				num_philo;
	int				fork_left;
	int				fork_right;
}					t_philo_info;


int					ft_atoi(const char *str);
void				ft_itoa_write(long int num);
void				ft_print_philo(long int timestamp, int philo, char action);
int					ft_save_args(int argc, char **argv, t_general_info *info);
long int			ft_get_current_time(struct timeval current_time
					, struct timeval init_time);
pthread_mutex_t		*ft_initialize_fork_locks(t_general_info general);
void				*philo_get_forks(t_philo_info *philo);
void				ft_get_forks_position(t_philo_info *philo);
void				*philo_eat(t_philo_info *philo);
void				*philo_sleep(t_philo_info philo);
void				*philo_think(t_philo_info philo);

#endif
