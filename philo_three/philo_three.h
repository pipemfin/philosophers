#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_table
{
	int					count;
	int					die_t;
	int					eat_t;
	int					sleep_t;
	int					meals_max;
	struct timeval		start;
	pid_t				*pids;
	sem_t				*forks;
	sem_t				*tribune;
}						t_table;

typedef struct s_philo
{
	int					number;
	int					meals_count;
	struct timeval		last_eat;
	pthread_t			thread;
	t_table				*table;
	sem_t				*eating;
	struct timeval		corrector;
	struct timeval		current;
	long int			start;
	long int			status;
	long int			time;
}						t_philo;

void		custom_usleep(int ms, t_philo *philo);
int			ft_atoi(const char *str);
int			ft_isdigit(int a);
void		check_input_params(int argc, char **argv, int i, int j);
t_table		*table_initialization(int argc, char **argv);
t_philo		**philosophers_initialization(t_table *table);
void		*clear_philosophers(t_philo **philosophers, int mode);
void		*clear_table(t_table *table);
void		get_forks_from_table(t_philo *philosopher);
void		put_forks_on_table(t_philo *philosopher);
void		control_philosopher(t_table *table, t_philo *philo);
void		status_print(t_table *table, t_philo *philosopher, int id);
char		*ft_itoa(int n);
int			ft_strlen(char *str);
void		kill_all(t_table *table);
void		status_print(t_table *table, t_philo *philosopher, int id);
void		unlink_semaphores(t_philo **philosophers);
int			custom_exit(t_philo **philo, t_table *table, int code, int mode);

#endif