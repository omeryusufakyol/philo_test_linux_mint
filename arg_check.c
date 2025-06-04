#include "philo.h"

int argument_checker(int ac, char **av)
{
    int i;
    int j;

    j = 0;
    i = 1;
    while (i < ac)
    {
        j = 0;
        if (av[i][0] == '0')
            return (0);
        while (av[i][j])
        {
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}
