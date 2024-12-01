#include "../philo.h"

int	if_all_digit(char *str)
{
    int i;

    if (!str || str[0] == '\0')
        return (1);
    i = 0;
    while (str[i] != '\0')
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOS || ft_atoi(argv[1]) <= 0
		|| if_all_digit(argv[1]))
		return (ft_putendl_fd("Invalid philosophers number", 1),2);
	if (ft_atoi(argv[2]) < 60 || if_all_digit(argv[2]))
		return (ft_putendl_fd("Invalid time to die number", 1),3);
	if (ft_atoi(argv[3]) < 60 || if_all_digit(argv[3]))
		return (ft_putendl_fd("Invalid time to eat number", 1),4);
	if (ft_atoi(argv[4]) < 60 || if_all_digit(argv[4]))
		return (ft_putendl_fd("Invalid time to sleep number", 1),5);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || if_all_digit(argv[5])))
		return (ft_putendl_fd("Invalid number of time each philosopher should eat", 1),6);
	return (0);
}