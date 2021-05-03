#include "philo_three.h"

void	ft_print_philo(t_philo *philo, int action)
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

void	ft_print_ended(t_env *env)
{
	write(1, "All philos have eaten ", 22);
	ft_itoa_write(env->meal_limit);
	if (env->meal_limit > 1)
		write(1, " rounds.", 7);
	else
		write(1, " round.", 7);
}
