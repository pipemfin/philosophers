#include "philo_three.h"

void	control_philosopher(t_table *table, t_philo *philo)
{
	int				control_philosophers_life;
	long int		status;
	struct timeval	current;

	pthread_detach(philo->thread);
	control_philosophers_life = 1;
	while (control_philosophers_life)
	{
		if (philo->last_eat.tv_usec != -1
			&& table->meals_max != philo->meals_count)
		{
			if (gettimeofday(&(current), NULL) == -1)
				write(2, "Time error!\n", 12);
			sem_wait(philo->eating);
			status = ((current.tv_sec * 1000000 + current.tv_usec) / 1000)
				- ((philo->last_eat.tv_sec * 1000000
						+ philo->last_eat.tv_usec) / 1000);
			sem_post(philo->eating);
			if (status > (philo->table->die_t))
			{
				sem_wait(philo->eating);
				status_print(table, philo, 4);
			}
		}
	}
}

void	status_print(t_table *table, t_philo *philosopher, int id)
{
	int				timestamp;
	struct timeval	current;

	if (sem_wait(table->tribune))
		write(2, "Semaphore tribune error!\n", 25);
	if (gettimeofday(&current, NULL) == -1)
		write(2, "Time error!\n", 12);
	timestamp = ((current.tv_sec * 1000000 + current.tv_usec)
			/ 1000) - ((table->start.tv_sec * 1000000 + table->start.tv_usec)
			/ 1000);
	if (id == 1)
		printf("%d %d is eating\n", timestamp, philosopher->number);
	else if (id == 2)
		printf("%d %d is sleeping\n", timestamp, philosopher->number);
	else if (id == 3)
		printf("%d %d is thinking\n", timestamp, philosopher->number);
	else if (id == 4)
	{
		printf("%d %d died\n", timestamp, philosopher->number);
		exit (1);
	}
	else if (id == 5)
		printf("%d %d has taken a fork\n", timestamp, philosopher->number);
	if (sem_post(table->tribune))
		write(2, "Semaphore tribune error!\n", 25);
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

void	kill_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->count)
		kill(table->pids[i], 1);
	exit(1);
}
