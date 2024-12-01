#include "../philo.h"

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_of_philos;
		data->philos[i].data = data;
	}
	return (0);
}

int	init_forks(pthread_mutex_t *forks, int count)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < count)
	{
		ret = pthread_mutex_init(&forks[i], NULL);
		if (ret != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (ret);
		}
	}
	return (0);
}

int init_data(char **argv, t_data *data)
{
	memset(data, 0, sizeof(*data));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0 ||
        pthread_mutex_init(&data->last_meal_lock, NULL) != 0 ||
        pthread_mutex_init(&data->eaten_enough_lock, NULL) != 0)
    {
        ft_putendl_fd("Error initializing mutex", 1);
        return (1);
    }
	data->num_of_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->finished = 0;
    data->num_required_meals = argv[5] ? atoi(argv[5]) : -1;
	return (0);
}
