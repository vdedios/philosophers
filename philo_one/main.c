/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:33:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/29 18:01:52 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philo_eat(void *ptr)
{
	ft_print_philo(123456, 0, 'e');
	return (NULL);
}

void	*philo_sleep(void *ptr)
{
	ft_print_philo(123456, 0, 's');
	return (NULL);
}

void	*philo_think(void *ptr)
{
	ft_print_philo(123456, 0, 't');
	return (NULL);
}

int		main(int argc, char **argv)
{
	pthread_t		philo;
	t_philo_info	info;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(1, "wrong number of args :(\n", 24);
		return (0);
	}
	if (!ft_save_args(argc, argv, &info))
	{
		write(1, "wrong args :(\n", 14);
		return (0);
	}
	pthread_mutex_init(&info.lock, NULL);
	pthread_create(&philo, NULL, philo_eat, (void *)&info);
	pthread_join(philo, NULL);
	pthread_mutex_destroy(&info.lock);
	return (0);
}
