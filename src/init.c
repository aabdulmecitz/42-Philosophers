#include "philo.h"

int **arg_int_values(int argc, const char *argv[])
{
    char **value_series_str;
    int **values;
    int i;

    value_series_str = argv++;
    argc--;
    values = malloc(sizeof(int) * argc);
    if (!values)
        return (NULL);
    i = 0;
    while (i < argc)
    {
        if (values[i] = ft_atol(value_series_str[i]) <= 0)
            return(free(values), NULL);
        i++;
    }
}

void init_simulation(t_simulation* simulation, int argc, const char *argv[])
{
    t_simulation *simulation;
    int **values = arg_int_values(argc, argv);

    simulation = (sizeof(t_simulation));
    if(!simulation && !values)
        return;
    simulation->philosophers = NULL;
    simulation->num_philosophers = values[0];
    simulation->time_to_die = values[1];
    simulation->time_to_eat = values[2];
    simulation->time_to_sleep = values[3];
    if (argc == 5)
        simulation->num_meals = values[4];
    else
        simulation->num_meals = -1;
    simulation->dead_flag = 0;
    free(values);
    //I m not sure for this free 
}

void init_philosophers(t_simulation *simulation)
{

}