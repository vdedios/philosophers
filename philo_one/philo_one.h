/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 17:46:19 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/29 18:01:41 by vde-dios         ###   ########.fr       */
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

int					ft_atoi(const char *str);
void				ft_itoa_write(long int num);
void				ft_print_philo(long int timestamp, int philo, char action);
int					ft_save_args(int argc, char **argv, t_philo_info *info);

/*
** number_of_philosophers time_to_die time_to_eat time_to_sleep
** [number_of_times_each_philosopher_must_eat]
*/

typedef struct		s_philo_info{
	pthread_mutex_t lock;
	long int		time;
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
}					t_philo_info;

#endif
