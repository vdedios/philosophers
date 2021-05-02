#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int	nbr;

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
	long int	i;

	i = 1;
	while (n >= 10)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

void	ft_itoa_write(unsigned long long n)
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

int	ft_save_args(int argc, char **argv, t_env *info)
{
	info->n_philos = ft_atoi(argv[1]);
	if (!info->n_philos
		|| !(info->time_die = ft_atoi(argv[2]))
		|| !(info->time_eat = ft_atoi(argv[3]))
		|| !(info->time_sleep = ft_atoi(argv[4])))
		return (0);
	if (argc == 6)
	{
		info->meal_limit = ft_atoi(argv[5]);
		if (!info->meal_limit)
			return (0);
	}
	else
		info->meal_limit = -1;
	return (1);
}

void	ft_print_philo(t_philo *philo, int action)
{
	if (action == FINISH)
	{
		write(1, "All philos have eaten ", 22);
		ft_itoa_write((philo->env)->meal_limit);
		if ((philo->env)->meal_limit > 1)
			write(1, " rounds.", 7);
		else
			write(1, " round.", 7);
	}
	else
	{
		ft_itoa_write(get_time() - (philo->env)->init_time);
		write(1, " philosopher_", 13);
		ft_itoa_write(philo->pos);
		if (action == GOT_FORK)
			write(1, " has taken a fork\n", 18);
		else if (action == EATING)
			write(1, " is eating\n", 11);
		else if (action == SLEEPING)
			write(1, " is sleeping\n", 13);
		else if (action == THINKING)
			write(1, " is thinking\n", 13);
		else if (action == DEAD)
			write(1, " has died\n", 10);
	}
}
