#include "philo.h"

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

static int  init_forks(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (0);
    i = 0;
    while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (!init_philos(data))
		return (0);
	return (1);
}

int init_all(t_data *data, int ac, char **av)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->stop_simulation = 0;
    data->has_optional_arg = 0;
    data->must_eat = -1;
    if (ac == 6)
        data->has_optional_arg = 1;
    if (data->has_optional_arg == 1)
        data->must_eat = ft_atoi(av[5]);
    if (!init_forks(data))
        return (0);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->simulation_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (0);
	return (1);
}
