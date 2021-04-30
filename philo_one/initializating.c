#include "philo_one.h"

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

pthread_mutex_t	**table_setting(t_table	*table)
{
	int					i;
	pthread_mutex_t		**forks;

	i = -1;
	table->tribune = malloc(sizeof(pthread_mutex_t));
	if (table->tribune == NULL)
		return (NULL);
	if (pthread_mutex_init(table->tribune, NULL) != 0)
		return (NULL);
	forks = malloc(sizeof(pthread_mutex_t *) * table->count);
	if (forks == NULL)
		return (NULL);
	while (++i < table->count)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(forks[i], NULL) != 0)
		{
			free(forks[i]);
			return (NULL);
		}
	}
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
		return (clear_table(table, 1));
	return (table);
}

static int	give_forks(t_table *table, t_philo	**philosophers)
{
	int	i;

	i = -1;
	while (++i < table->count)
	{
		philosophers[i]->eating = malloc(sizeof(pthread_mutex_t));
		if (philosophers[i]->eating == NULL)
			return (1);
		if (pthread_mutex_init(philosophers[i]->eating, NULL) != 0)
			return (1);
		if (i - 1 < 0)
			philosophers[i]->left = table->forks[table->count - 1];
		else
			philosophers[i]->left = table->forks[i - 1];
		philosophers[i]->right = table->forks[i];
	}
	return (0);
}

t_philo	**philosophers_initialization(t_table *table, int i)
{
	t_philo	**philosophers;

	philosophers = malloc(sizeof(t_philo *) * table->count);
	if (philosophers == NULL)
		return (NULL);
	while (++i < table->count)
	{
		philosophers[i] = malloc(sizeof(t_philo));
		if (philosophers[i] == NULL)
		{
			clear_table(table, 1);
			return (clear_philosophers(philosophers, 1));
		}
		philosophers[i]->table = table;
		philosophers[i]->number = i + 1;
		philosophers[i]->meals_count = 0;
		philosophers[i]->last_eat.tv_usec = -1;
	}
	if (give_forks(table, philosophers))
	{
		clear_table(table, 0);
		return (clear_philosophers(philosophers, 1));
	}
	return (philosophers);
}
