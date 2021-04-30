#include "philo_two.h"

void	check_input_params(int argc, char **argv, int i, int j)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Not enough/too much input parametrs!\n", 37);
		exit(1);
	}
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, "Parameters must be a positive numbers!\n", 39);
				exit(1);
			}
		}
		if (ft_atoi(argv[i]) <= 0)
		{
			write(2, "Parameters must be more than zero!\n", 35);
			exit(1);
		}
	}
}

sem_t	*table_setting(t_table	*table)
{
	sem_t	*forks;

	sem_unlink("/tribune");
	sem_unlink("/forks");
	table->tribune = sem_open("/tribune", O_CREAT, 0666, 1);
	if (table->tribune <= 0)
	{
		table->tribune = NULL;
		return (NULL);
	}
	forks = sem_open("/forks", O_CREAT, 0666, table->count);
	if (forks <= 0)
		return (NULL);
	return (forks);
}

t_table	*table_initialization(int argc, char **argv)
{
	t_table	*table;

	check_input_params(argc, argv, 0, -1);
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->count = ft_atoi(argv[1]);
	table->die_t = ft_atoi(argv[2]);
	table->eat_t = ft_atoi(argv[3]);
	table->sleep_t = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_max = ft_atoi(argv[5]);
	else
		table->meals_max = -1;
	table->forks = table_setting(table);
	table->gorged_philo = 0;
	if (table->forks == NULL)
		return (clear_table(table));
	return (table);
}

static int	init_semaphores(t_philo	**philosophers)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < philosophers[0]->table->count)
	{
		str = ft_itoa(i + 1);
		if (str == NULL)
			return (custom_exit(philosophers, philosophers[0]->table, 1, 0));
		sem_unlink(str);
		philosophers[i]->eating = sem_open(str, O_CREAT, 0666, 1);
		if (philosophers[i]->eating == NULL)
			return (custom_exit(philosophers, philosophers[0]->table, 1, 0));
		free(str);
	}
	return (0);
}

t_philo	**philosophers_initialization(t_table *table)
{
	int		i;
	t_philo	**philosophers;

	philosophers = malloc(sizeof(t_philo *) * table->count);
	if (philosophers == NULL)
		return (NULL);
	i = -1;
	while (++i < table->count)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		if (philosophers[i] == NULL)
		{
			clear_table(table);
			return (clear_philosophers(philosophers, 1));
		}
		philosophers[i]->table = table;
		philosophers[i]->number = i + 1;
		philosophers[i]->meals_count = 0;
		philosophers[i]->last_eat.tv_usec = -1;
	}
	if (init_semaphores(philosophers))
		return (NULL);
	return (philosophers);
}
