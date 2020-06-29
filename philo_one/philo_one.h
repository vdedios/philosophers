#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
#include <limits.h>

int		ft_atoi(const char *str);
void	ft_itoa_write(long int num);
void	ft_print_philo(long int timestamp, int philo, char action);

#endif
