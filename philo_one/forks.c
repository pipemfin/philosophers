#include "philo_one.h"

void	get_forks_from_table(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->left);
	pthread_mutex_lock(philosopher->right);
}

void	put_forks_on_table(t_philo *philosopher)
{
	pthread_mutex_unlock(philosopher->right);
	pthread_mutex_unlock(philosopher->left);
}
