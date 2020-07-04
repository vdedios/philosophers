/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:49:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/07/04 22:18:16 by vde-dios         ###   ########.fr       */
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

void			ft_print_philo(long int timestamp, int philo, char action)
{
	ft_itoa_write(timestamp);
	write(1, " philosopher ", 13);
	ft_itoa_write((long int)philo);
	if (action == 'f')
		write(1, " has taken a fork\n", 18);
	else if (action == 'e')
		write(1, " is eating\n", 11);
	else if (action == 's')
		write(1, " is sleeping\n", 13);
	else if (action == 't')
		write(1, " is thinking\n", 13);
	else if (action == 'd')
		write(1, " died\n", 6);
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

pthread_mutex_t	*ft_initialize_fork_locks(t_general_info general)
{
	int i;
	pthread_mutex_t	*lock_fork;

	i = -1;
	if (!(lock_fork = malloc(general.n_philos * sizeof(pthread_mutex_t))))
		return (NULL);
	while (++i < general.n_philos)
		pthread_mutex_init(&lock_fork[i], NULL);
	return (lock_fork);
}

void			ft_get_forks_position(t_philo_info *philo)
{
	philo->fork_right = philo->num_philo;
	philo->fork_left = (philo->num_philo - 1) >= 0
		? philo->num_philo - 1 : philo->general->n_philos - 1;
}
