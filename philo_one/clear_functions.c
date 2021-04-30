#include "philo_one.h"

void	*clear_philosophers(t_philo **philosophers, int mode)
{
	int	i;

	if (philosophers == NULL)
		return (NULL);
	i = -1;
	if (mode == 1)
	{
		while (philosophers[++i])
		{
			free(philosophers[i]);
			free(philosophers[i]->eating);
		}
	}
	else if (mode == 0)
	{
		while (++i < philosophers[0]->table->count)
		{
			free(philosophers[i]);
			free(philosophers[i]->eating);
		}
	}
	free(philosophers);
	return (NULL);
}

void	*clear_table(t_table *table, int mode)
{
	int	i;

	if (table->forks != NULL)
	{
		i = -1;
		if (mode == 1)
		{
			while (table->forks[++i])
				free(table->forks[i]);
		}
		if (mode == 0)
		{
			while (++i < table->count)
				free(table->forks[i]);
		}
		free(table->forks);
	}
	if (table != NULL)
		free(table);
	return (NULL);
}

int	custom_exit(t_philo **philo, t_table *table, int code, int mode)
{
	clear_philosophers(philo, mode);
	clear_table(table, mode);
	return (code);
}
