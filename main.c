#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
        return (ft_putendl_fd("WRONG NUMBER OF ARGS\n",1), 2);
	if (check_args(argv) != 0)
		return (1);
	if (init_data(argv,&data) != 0)
		return (1);
	if (init_forks(data.forks,data.num_of_philos )!= 0)
		return (1);
	if (init_philos(&data)!= 0)
		return (1);
	data.start_time = get_current_time();
	run_philos(&data);
	threads_join(&data);
	destroy_locks(&data);
	return (0);
}
