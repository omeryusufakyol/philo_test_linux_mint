#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    print_action("is sleeping", philo);
    ft_usleep(philo->data->time_to_sleep);
}

void    think(t_philo *philo)
{
    print_action("is thinking", philo);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    print_action("has taken a fork", philo);
    if (philo->data->num_philos == 1)
    {
        ft_usleep(philo->data->time_to_die);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_lock(philo->left_fork);
    print_action("has taken a fork", philo);
    print_action("is eating", philo);
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->last_meal = get_time();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->data->meal_lock);
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (!dead_check(philo))
    {
        eat(philo);
        philo_sleep(philo);
        think(philo);
    }
    return (arg);
}
