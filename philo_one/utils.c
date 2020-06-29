/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:49:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/29 17:27:27 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_isthespace(int c)
{
	if (c == '\v' || c == '\n' || c == '\t' ||
		c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int sign;
	int nbr;

	sign = 1;
	nbr = 0;
	while (ft_isthespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (nbr * sign);
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
