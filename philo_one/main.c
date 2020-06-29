/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:33:37 by vde-dios          #+#    #+#             */
/*   Updated: 2020/06/29 17:24:48 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** number_of_philosophers time_to_die time_to_eat time_to_sleep
** [number_of_times_each_philosopher_must_eat]
*/

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

int main(int argc, char **argv)
{
	pthread_t 		philo;
	pthread_mutex_t lock;

	pthread_mutex_init(&lock, NULL);
	pthread_create(&philo, NULL, philo_eat, (void *)&lock);
	pthread_join(philo, NULL);
	pthread_mutex_destroy(&lock);
	return (0);
}
