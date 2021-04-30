#include "philo_three.h"

void	get_forks_from_table(t_philo *philosopher)
{
	if (sem_wait(philosopher->table->forks))
		write(2, "Semaphore error!\n", 17);
	if (sem_wait(philosopher->table->forks))
		write(2, "Semaphore error!\n", 17);
}

void	put_forks_on_table(t_philo *philosopher)
{
	if (sem_post(philosopher->table->forks))
		write(2, "Semaphore unlock error!\n", 24);
	if (sem_post(philosopher->table->forks))
		write(2, "Semaphore unlock error!\n", 24);
}
