#include "philo.h"

int start_simulation(t_data *data)
{
    int i;
    pthread_t   monitor_thread;

    data->start_time = get_time();
    if (data->start_time == -1)
        return (0);
    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].last_meal = get_time();
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, &monitor, data->philos) != 0)
    {
        destroy_all("Error: Failed to create monitor thread", data);
        return (0);
    }
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != 0)
        {
            destroy_all("Error: Failed to create thread for philos", data);
            return (0);
        }
        i++;
    }
    i = 0;
    if (pthread_join(monitor_thread, NULL) != 0)
        destroy_all("Error: Join error for monitor thread", data);
    while (i < data->num_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
        {
            destroy_all("Error: Join error for philos' threads", data);
            return (0);
        }
        i++;
    }
    return (1);
}
