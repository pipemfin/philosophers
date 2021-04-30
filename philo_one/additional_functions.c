/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerrod <jjerrod@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:07:09 by jjerrod           #+#    #+#             */
/*   Updated: 2021/04/28 23:41:20 by jjerrod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_isdigit(int a)
{
	if (a > 47 && a < 58)
		return (1);
	else
		return (0);
}

static int	ft_str_to_int(const char *str, int a, int b)
{
	int	c;
	int	d;
	int	number;

	d = a - 1;
	c = 1;
	number = 0;
	while (d > b - 1)
	{
		number = number + (str[d] - 48) * c;
		c = c * 10;
		--d;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	c = 1;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
	{
		++a;
		++b;
	}
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			c = -1;
		++a;
		++b;
	}
	while (str[a] >= '0' && str[a] <= '9')
		++a;
	return (c * ft_str_to_int(str, a, b));
}

void	custom_usleep(int ms, t_philo *philo)
{
	t_table			*table;

	table = philo->table;
	philo->status = 0;
	philo->start = (table->start.tv_sec * 1000000
			+ table->start.tv_usec) / 1000;
	gettimeofday(&(philo->current), NULL);
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
