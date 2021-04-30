#include "philo_one.h"

void	detach_pthreads(t_philo **philo)
{
	int	i;
	int	count;

	i = 0;
	count = philo[0]->table->count;
	while (i < count)
		if (pthread_detach(philo[i++]->thread))
			write(2, "Detach error\n", 13);
}

static long int	get_status(t_philo **philo, int i)
{
	long int		status;
	struct timeval	current;

	if (gettimeofday(&current, NULL) == -1)
		write(2, "Time error!\n", 12);
	status = ((current.tv_sec * 1000000
				+ current.tv_usec) / 1000)
		- ((philo[i]->last_eat.tv_sec * 1000000
				+ philo[i]->last_eat.tv_usec) / 1000);
	return (status);
}

void	control_philosophers(t_table *table, t_philo **philo, int i)
{
	int				control_philosophers_life;
	long int		status;

	control_philosophers_life = 1;
	while (control_philosophers_life)
	{
		++i;
		if (i == table->count)
			i = 0;
		if (philo[i]->last_eat.tv_usec != -1
			&& table->meals_max != philo[i]->meals_count)
		{
			pthread_mutex_lock(philo[i]->eating);
			status = get_status(philo, i);
			pthread_mutex_unlock(philo[i]->eating);
			if (status > (philo[i]->table->die_t))
			{
				pthread_mutex_lock(philo[i]->eating);
				status_print(table, philo[i], 4);
			}
		}
		if (table->gorged_philo == table->count)
			break ;
	}
}
