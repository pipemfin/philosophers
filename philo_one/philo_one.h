#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int					count;
	int					die_t;
	int					eat_t;
	int					sleep_t;
	int					meals_max;
	int					gorged_philo;
	struct timeval		start;
	struct timeval		current;
	pthread_mutex_t		**forks;
	pthread_mutex_t		*tribune;
	void				**philosophers;
}						t_table;

typedef struct s_philo
{
	int					number;
	int					meals_count;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		*eating;
	pthread_t			thread;
	struct timeval		last_eat;
	struct timeval		corrector;
	struct timeval		current;
	long int			start;
	long int			status;
	long int			time;
	t_table				*table;
}						t_philo;

void			custom_usleep(int ms, t_philo *philo);
int				ft_atoi(const char *str);
int				ft_isdigit(int a);
void			*clear_split_reverse(t_philo **split, int i);
t_table			*table_initialization(int argc, char **argv);
t_philo			**philosophers_initialization(t_table *table, int i);
void			*clear_philosophers(t_philo **philosophers, int mode);
void			*clear_table(t_table *table, int mode);
void			put_forks_on_table(t_philo *philosopher);
void			get_forks_from_table(t_philo *philosopher);
void			control_philosophers(t_table *table, t_philo **philo, int i);
void			status_print(t_table *table, t_philo *philosopher, int id);
void			detach_pthreads(t_philo **philo);
int				custom_exit(t_philo **philo, t_table *table,
					int code, int mode);

#endif