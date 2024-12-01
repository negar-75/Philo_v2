#ifndef PHILO_H
# define PHILO_H

#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX_PHILOS 200

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				has_eaten_enough;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	size_t			time_of_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_required_flag;
	int				num_required_meals;
	size_t			start_time;
	pthread_t		monitor;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	eaten_enough_lock;
	struct s_philo	philos[MAX_PHILOS];
	int				finished;
}					t_data;

// * args_validation.c *
int					check_args(char **argv);

// * helper.c *
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
size_t				timestamp(t_data *data);
int					print_message(t_philo *philo, char *str, int force_print);

// * init.c *
int					init_philos(t_data *data);
int					init_forks(pthread_mutex_t *forks, int count);
int					init_data(char **argv, t_data *data);

// * thread_utils.c *
int					threads_join(t_data *data);
void				destroy_locks(t_data *data);
void				meals_eaten_util(t_philo *philo);

// * monitor.c *
void				*monitor(void *arg);

// * routine.c *
void				*routine(void *arg);

// * thread.c *
void				run_philos(t_data *data);

// * libft *
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_atoi(const char *str);

#endif