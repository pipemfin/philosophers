#include "philo_two.h"

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

	detach_pthreads(philo);
	control_philosophers_life = 1;
	while (control_philosophers_life)
	{
		++i;
		if (i == table->count)
			i = 0;
		if (philo[i]->last_eat.tv_usec != -1
			&& table->meals_max != philo[i]->meals_count)
		{
			sem_wait(philo[i]->eating);
			status = get_status(philo, i);
			sem_post(philo[i]->eating);
			if (status > (table->die_t))
			{
				sem_wait(philo[i]->eating);
				status_print(table, philo[i], 4);
			}
		}
		if (table->gorged_philo == table->count)
			break ;
	}
}

void	custom_usleep(int ms, t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	philo->status = 0;
	if (gettimeofday(&(philo->current), NULL) == -1)
		write(2, "Time error!\n", 12);
	philo->start = (table->start.tv_sec * 1000000
			+ table->start.tv_usec) / 1000;
	philo->time = philo->start
		+ ((philo->current.tv_sec * 1000000
				+ philo->current.tv_usec) / 1000) + ms;
	while (philo->status < philo->time)
	{
		usleep(100);
		gettimeofday(&(philo->corrector), NULL);
		philo->status = philo->start + ((philo->corrector.tv_sec * 1000000
					+ philo->corrector.tv_usec) / 1000);
	}
}
