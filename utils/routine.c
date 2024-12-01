#include "../philo.h"

void	meals_eaten_util(t_philo *philo)
{
	philo->meals_eaten += 1;
	pthread_mutex_lock(&philo->data->eaten_enough_lock);
	if (!philo->has_eaten_enough && (philo->meals_eaten == philo->data->num_required_meals))
		philo->has_eaten_enough = 1;
	pthread_mutex_unlock(&philo->data->eaten_enough_lock);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->id % 2 == 1 ? philo->left_fork : philo->right_fork]));
	print_message(philo, "has taken a fork ", 0);
	if (philo->data->num_of_philos == 1)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
		return (1);
	}
	pthread_mutex_lock(&(philo->data->forks[philo->id % 2 == 1 ? philo->right_fork : philo->left_fork]));
	print_message(philo, "has taken a fork ", 0);
	pthread_mutex_lock(&philo->data->last_meal_lock);
	philo->time_of_last_meal = timestamp(philo->data);
	pthread_mutex_unlock(&philo->data->last_meal_lock);
	print_message(philo, "is eating ", 0);
	ft_usleep(philo->data->time_to_eat);
	meals_eaten_util(philo);
	pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
	print_message(philo, "is sleeping ", 0);
	ft_usleep(philo->data->time_to_sleep);
	print_message(philo, "is thinking ", 0);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (1)
	{
		if (eat(philo))
		{
			pthread_mutex_lock(&philo->data->write_lock);
			philo->data->finished = 1;
			pthread_mutex_unlock(&philo->data->write_lock);
			return (NULL);
		}
		pthread_mutex_lock(&philo->data->write_lock);
		if (philo->data->finished == 1)
		{
			pthread_mutex_unlock(&philo->data->write_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->write_lock);
		if (philo->data->num_of_philos % 2 == 1)
			ft_usleep((philo->data->time_to_eat * 2) - (philo->data->time_to_sleep));
	}
	return (NULL);
}
