# include "../philo.h"

void	run_philos(t_data *data)
{
	int	i;

	pthread_create(&data->monitor, NULL, monitor, (void *)data);
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->last_meal_lock);
		data->philos[i].time_of_last_meal = timestamp(data);
		pthread_create(&data->philos[i].thread, NULL, routine,
			(void *)&data->philos[i]);
		pthread_mutex_unlock(&data->last_meal_lock);
	}
}

int	threads_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (write(2, "pthread_join error\n", 19), 1);
	if (pthread_join(data->monitor, NULL) != 0)
		return (write(2, "pthread_join error\n", 19), 1);
	return (0);
}

void	destroy_locks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write_lock));
}
