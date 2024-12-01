#include "../philo.h"

int	print_message(t_philo *philo, char *str, int force_print)
{
	if (pthread_mutex_lock(&(philo->data->write_lock)))
		return (1);
	if (force_print || !philo->data->finished)
		printf("%zu\t%d %s\n", timestamp(philo->data), philo->id, str);
	if (pthread_mutex_unlock(&(philo->data->write_lock)))
		return (1);
	return (0);
}

size_t	timestamp(t_data *data)
{
	return (get_current_time() - data->start_time);
}

size_t	get_current_time(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "Time of day Error\n", 18);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;
	
	start = get_current_time();
	while (get_current_time() - start < milliseconds)
		usleep(500);
	return (0);
}
