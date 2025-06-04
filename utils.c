#include "philo.h"

long long  get_time()
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        printf("Error: gettimeofday() error\n");
        return (-1);
    }
    return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

void	print_action(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = get_time() - philo->data->start_time;
	if (!dead_check(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	destroy_all(char *str, t_data *data)
{
	int	i;

	if (str)
		printf("Error: %s\n", str);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->simulation_lock);
	free(data->forks);
	free(data->philos);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}