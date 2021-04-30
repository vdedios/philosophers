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

static long int	ft_size_num(long int n)
{
	long int i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

void			ft_itoa_write(unsigned long long n)
{
	long int	size;
	char		digit;

	size = ft_size_num(n);
	while (size > 0)
	{
		digit = n / size + '0';
		write(1, &digit, 1);
		n = n % size;
		size /= 10;
	}
}

int				ft_save_args(int argc, char **argv, t_env *info)
{
	if (!(info->n_philos = ft_atoi(argv[1]))
			|| !(info->time_die = ft_atoi(argv[2]))
			|| !(info->time_eat = ft_atoi(argv[3]))
			|| !(info->time_sleep = ft_atoi(argv[4])))
		return (0);
	if (argc == 6)
	{
		if (!(info->n_eat = ft_atoi(argv[5])))
			return (0);
	}
	else
		info->n_eat = -1;
	return (1);
}
