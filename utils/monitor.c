#include "../philo.h"

int	meals_check(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->eaten_enough_lock);
		if (!(data->philos[i].has_eaten_enough))
			return (pthread_mutex_unlock(&data->eaten_enough_lock), 0);
		pthread_mutex_unlock(&data->eaten_enough_lock);
	}
	usleep(10);
	return (1);
}

int	is_dead(t_data *data)
{
	size_t	dead_time;
	int		i;

	i = -1;
	if (timestamp(data) < data->time_to_die)
		dead_time = 0;
	else
		dead_time = timestamp(data) - data->time_to_die;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->last_meal_lock);
		if (data->philos[i].time_of_last_meal <= dead_time && dead_time != 0)
		{
			print_message(&(data->philos[i]), "died ", 1);
			pthread_mutex_lock(&data->write_lock);
			data->finished = 1;
			pthread_mutex_unlock(&data->last_meal_lock);
			return (pthread_mutex_unlock(&data->write_lock), 1);
		}
		pthread_mutex_unlock(&data->last_meal_lock);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_dead(data))
			return (NULL);
		if (data->num_required_meals != -1 && meals_check(data))
		{
			pthread_mutex_lock(&data->write_lock);
			data->finished = 1;
			return (pthread_mutex_unlock(&data->write_lock), NULL);
		}
		usleep(100);
	}
	return (NULL);
}
