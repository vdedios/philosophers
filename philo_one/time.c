#include "philo_one.h"

t_time_ms	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((t_time_ms)(current.tv_sec * 1000 + current.tv_usec / 1000));
}

void	better_usleep(t_time_ms time_to_sleep)
{
	t_time_ms	stop;

	stop = get_time() + time_to_sleep;
	while (get_time() < stop)
		usleep (1);
}
