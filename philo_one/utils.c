/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:49:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/29 18:01:41 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_atoi(const char *str)
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

void		ft_itoa_write(long int num)
{
	char		digit;

	if (num / 10 > 0)
		ft_itoa_write(num / 10);
	digit = num % 10 + '0';
	write(1, &digit, 1);
}

void		ft_print_philo(long int timestamp, int philo, char action)
{
	ft_itoa_write(timestamp);
	write(1, " philosopher ", 13);
	ft_itoa_write((long int)philo);
	if (action == 'f')
		write(1, " has taken a fork\n", 18);
	else if (action == 'e')
		write(1, " is eating\n", 11);
	else if (action == 's')
		write(1, " is sleaping\n", 13);
	else if (action == 't')
		write(1, " is thinking\n", 13);
	else if (action == 'd')
		write(1, " died\n", 6);
}

int		ft_save_args(int argc, char **argv, t_philo_info *info)
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

