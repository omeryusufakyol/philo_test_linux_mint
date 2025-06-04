#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	int		eat_count;
	long long	last_meal;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	has_optional_arg;
	int	stop_simulation;
	long long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	meal_lock;
	t_philo	*philos;
}	t_data;

// arg_check.c
int argument_checker(int ac, char **av);

// utils.c
long long  get_time();
int	ft_usleep(size_t ms);
void	print_action(char *str, t_philo *philo);
void	destroy_all(char *str, t_data *data);
int	ft_atoi(char *str);

// init.c
int init_all(t_data *data, int ac, char **av);

// simulation.c
int start_simulation(t_data *data);

// cleanup.c
void	free_all(t_data *data);

// monitor.c
int dead_check(t_philo *philo);
void    *monitor(void *arg);

// routine.c
void    philo_sleep(t_philo *philo);
void    think(t_philo *philo);
void    eat(t_philo *philo);
void    *routine(void *arg);


#endif