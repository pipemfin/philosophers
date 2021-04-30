#include "philo_three.h"

void	unlink_semaphores(t_philo **philosophers)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < philosophers[0]->table->count)
	{
		str = ft_itoa(i + 1);
		if (str == NULL)
		{
			write(2, "Something is wrong with semaphores!\n", 36);
			return ;
		}
		if (philosophers[i]->eating != NULL)
			sem_unlink(str);
		free(str);
	}
}

void	*clear_philosophers(t_philo **philosophers, int mode)
{
	int	i;

	if (philosophers == NULL)
		return (NULL);
	i = -1;
	unlink_semaphores(philosophers);
	if (mode == 1)
	{
		while (philosophers[++i])
			free(philosophers[i]);
	}
	else if (mode == 0)
	{
		while (++i < philosophers[0]->table->count)
			free(philosophers[i]);
	}
	free(philosophers);
	return (NULL);
}

void	*clear_table(t_table *table)
{
	if (table->forks != NULL)
		sem_unlink("/forks");
	if (table->tribune != NULL)
		sem_unlink("/tribune");
	if (table != NULL)
		free(table);
	return (NULL);
}

int	custom_exit(t_philo **philo, t_table *table, int code, int mode)
{
	clear_philosophers(philo, mode);
	clear_table(table);
	return (code);
}
