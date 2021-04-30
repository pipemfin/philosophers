#include "philo_three.h"

void	philo_eat(t_philo *philosopher)
{
	get_forks_from_table(philosopher);
	status_print(philosopher->table, philosopher, 5);
	sem_wait(philosopher->eating);
	if ((gettimeofday(&(philosopher->last_eat), NULL)) == -1)
		write(2, "Time error!\n", 12);
	sem_post(philosopher->eating);
	status_print(philosopher->table, philosopher, 1);
	philosopher->meals_count += 1;
	custom_usleep(philosopher->table->eat_t, philosopher);
	put_forks_on_table(philosopher);
}

void	*philosophers_thinking(void *philosopher)
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
	exit(0);
}

void	start_thinking(t_table	*table, t_philo *philo)
{
	int	status;

	status = pthread_create(&(philo->thread),
			NULL, philosophers_thinking, philo);
	if (status != 0)
		write(2, "Can't create philosopher!\n", 26);
	control_philosopher(table, philo);
}

int	born_philosophers(t_table *table, t_philo **philos)
{
	int	i;
	int	status;

	i = -1;
	if ((gettimeofday(&(table->start), NULL) == -1))
		write(2, "Time error!\n", 12);
	while (++i < table->count)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
			start_thinking(table, philos[i]);
		usleep(10);
	}
	i = -1;
	status = 0;
	while (++i < table->count)
	{
		waitpid(0, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			kill_all(table);
			exit(custom_exit(philos, table, 1, 0));
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	**philosophers;

	table = table_initialization(argc, argv);
	if (table == NULL)
		return (1);
	philosophers = philosophers_initialization(table);
	if (philosophers == NULL)
		return (1);
	born_philosophers(table, philosophers);
	return (custom_exit(philosophers, table, 0, 0));
}
