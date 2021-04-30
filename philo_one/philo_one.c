#include "philo_one.h"

void	status_print(t_table *table, t_philo *philosopher, int id)
{
	long int	timestamp;

	pthread_mutex_lock(table->tribune);
	gettimeofday(&(table->current), NULL);
	timestamp = ((table->current.tv_sec * 1000000 + table->current.tv_usec)
			/ 1000) - ((table->start.tv_sec * 1000000 + table->start.tv_usec)
			/ 1000);
	if (id == 1)
		printf("%ld %d is eating\n", timestamp, philosopher->number);
	else if (id == 2)
		printf("%ld %d is sleeping\n", timestamp, philosopher->number);
	else if (id == 3)
		printf("%ld %d is thinking\n", timestamp, philosopher->number);
	else if (id == 4)
	{
		printf("%ld %d died\n", timestamp, philosopher->number);
		exit(custom_exit((t_philo **)table->philosophers, table, 1, 0));
	}
	else if (id == 5)
		printf("%ld %d has taken a fork\n", timestamp, philosopher->number);
	pthread_mutex_unlock(table->tribune);
}

static void	philo_eat(t_philo *philosopher)
{
	get_forks_from_table(philosopher);
	status_print(philosopher->table, philosopher, 5);
	pthread_mutex_lock(philosopher->eating);
	if ((gettimeofday(&(philosopher->last_eat), NULL)) == -1)
		write(2, "Time error!\n", 12);
	pthread_mutex_unlock(philosopher->eating);
	status_print(philosopher->table, philosopher, 1);
	philosopher->meals_count += 1;
	custom_usleep(philosopher->table->eat_t, philosopher);
	put_forks_on_table(philosopher);
}

static void	*philosophers_thinking(void *philosopher)
{
	int		cycle_of_life;
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	cycle_of_life = 1;
	while (cycle_of_life)
	{
		philo_eat(philo);
		if (philo->table->meals_max == philo->meals_count)
			break ;
		status_print(philo->table, philo, 2);
		custom_usleep(philo->table->sleep_t, philo);
		status_print(philo->table, philo, 3);
	}
	philo->table->gorged_philo += 1;
	return (philosopher);
}

static void	start_thinking(t_table	*table, t_philo **philo, int i)
{
	int		cycle_flag;
	int		status;
	int		parity;

	cycle_flag = 1;
	parity = 0;
	if (table->count % 2 == 1)
		parity = 1;
	if ((gettimeofday(&(table->start), NULL) == -1))
		write(2, "Time error!\n", 12);
	while (cycle_flag)
	{
		i += 2;
		if (i == (table->count + 1 - parity) || (table->count == 1 && i == 2))
			break ;
		else if (i == (table->count + parity))
			i = 1;
		status = pthread_create(&(philo[i]->thread),
				NULL, philosophers_thinking, philo[i]);
		usleep(10);
		if (status != 0)
			write(2, "Can't create philosopher!\n", 26);
	}
	detach_pthreads(philo);
	control_philosophers(table, philo, -1);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	**philosophers;

	table = table_initialization(argc, argv);
	if (table == NULL)
		return (1);
	philosophers = philosophers_initialization(table, -1);
	table->philosophers = (void **)philosophers;
	if (table == NULL)
		return (1);
	start_thinking(table, philosophers, -2);
	return (custom_exit(philosophers, table, 0, 0));
}
