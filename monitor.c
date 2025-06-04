#include "philo.h"

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simulation_lock);
	if (philo->data->stop_simulation == 1)
	{
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	return (0);
}

static int	check_if_dead(t_philo *philos)
{
	int			i;
	long long	now;

	i = 0;
	while (i < philos->data->num_philos)
	{
		now = get_time();
		pthread_mutex_lock(&philos->data->meal_lock);
		if ((now - philos[i].last_meal) >= philos->data->time_to_die)
		{
			pthread_mutex_unlock(&philos->data->meal_lock);
			print_action("died", &philos[i]);
			pthread_mutex_lock(&philos->data->simulation_lock);
			philos->data->stop_simulation = 1;
			pthread_mutex_unlock(&philos->data->simulation_lock);
			return (1);
		}
		pthread_mutex_unlock(&philos->data->meal_lock);
		i++;
	}
	return (0);
}

static int	check_all_ate(t_philo *philo)
{
	int	i;
	int	full;

	if (philo->data->must_eat == -1)
		return (0);
	i = 0;
	full = 0;
	while (i < philo->data->num_philos)
	{
		pthread_mutex_lock(&philo->data->meal_lock);
		if (philo[i].eat_count >= philo->data->must_eat)
			full++;
		pthread_mutex_unlock(&philo->data->meal_lock);
		i++;
	}
	if (full == philo->data->num_philos)
	{
		pthread_mutex_lock(&philo->data->simulation_lock);
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->simulation_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_if_dead(philo) || check_all_ate(philo))
			break ;
		usleep(100); // CPU tüketimini azaltmak için küçük gecikme
	}
	return (arg);
}