#include "philo.h"



int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong number of arguments!\n"), 1);
	if (!argument_checker(ac, av))
		return (printf("Error: Arguments must be positive number! (0 is not included)\n"), 1);
	if (!init_all(&data, ac, av))
		return (printf("Error: Something went wrong on init_data!\n"), 1);
	if (!start_simulation(&data))
		return (printf("Error: Simulation failed\n"), 1);
	free_all(&data);
	return (0);
}