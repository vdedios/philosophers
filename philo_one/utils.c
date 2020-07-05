/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:49:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/07/05 21:10:05 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_atoi(const char *str)
{
	int nbr;

	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (0);
	return (nbr);
}

void			ft_itoa_write(long int num)
{
	char		digit;

	if (num / 10 > 0)
		ft_itoa_write(num / 10);
	digit = num % 10 + '0';
	write(1, &digit, 1);
}

void			ft_print_philo(t_philo_info *philo, int action)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philo->general->message);
	gettimeofday(&current_time, NULL);
	ft_itoa_write(ft_get_current_time(current_time, philo->general->init_time));
	write(1, " philosopher_", 13);
	ft_itoa_write(philo->num_philo);
	if (action == GOT_FORK)
		write(1, " has taken a fork\n", 18);
	else if (action == EATING)
		write(1, " is eating\n", 11);
	else if (action == SLEEPING)
		write(1, " is sleeping\n", 13);
	else if (action == THINKING)
		write(1, " is thinking\n", 13);
	else if (action == IS_DEAD)
	{
		if (ft_get_current_time(current_time,
			philo->critical_time) > philo->general->time_die)
		{
			write(1, " died\n", 6);
			exit(1);
		}
	}
	pthread_mutex_unlock(&philo->general->message);
}

int				ft_save_args(int argc, char **argv, t_general_info *info)
{
	if (!(info->n_philos = ft_atoi(argv[1]))
		|| !(info->time_die = ft_atoi(argv[2]))
		|| !(info->time_eat = ft_atoi(argv[3]))
		|| !(info->time_sleep = ft_atoi(argv[4])))
		return (0);
	if (argc == 6
		&& !(info->n_eat = ft_atoi(argv[5])))
		return (0);
	return (1);
}

long int		ft_get_current_time(struct timeval current_time
				, struct timeval init_time)
{
	long int	t;

	t = (current_time.tv_sec - init_time.tv_sec) * 1000
		+ (current_time.tv_usec - init_time.tv_usec) / 1000;
	return (t);
}

void			*ft_init_locks(t_general_info *general)
{
	int i;

	i = -1;
	if (!(general->lock_fork = malloc(general->n_philos * sizeof(pthread_mutex_t))))
		return (NULL);
	if (!(general->locks = malloc(general->n_philos * sizeof(int))))
		return (NULL);
	while (++i < general->n_philos)
	{
		pthread_mutex_init(&general->lock_fork[i], NULL);
		general->locks[i] = 0;
	}
	pthread_mutex_init(&general->message, NULL);
	return (general->lock_fork);
}

void			ft_get_forks_position(t_philo_info *philo)
{
	philo->fork_right = philo->num_philo;
	philo->fork_left = (philo->num_philo - 1) >= 0
		? philo->num_philo - 1 : philo->general->n_philos - 1;
}
