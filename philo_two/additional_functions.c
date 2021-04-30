#include "philo_two.h"

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

static int	ft_howmany_digits(int n, int mode)
{
	int	a;

	a = 0;
	if (mode == 0)
	{
		while (n != 0)
		{
			n /= 10;
			++a;
		}
	}
	else if (mode == 1)
	{
		if (n < 0)
			a = -1;
		else
			a = 1;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		a;
	int		b;
	int		sign;

	b = ft_howmany_digits(n, 0);
	a = n;
	sign = ft_howmany_digits(n, 1);
	string = malloc(sizeof(char) * (b + 2));
	if (string == NULL)
		return (NULL);
	if (n < 0)
		++b;
	string[b--] = '\0';
	while (b >= 0)
	{
		string[b--] = (a % 10 * sign) + 48;
		a /= 10;
	}
	if (n < 0)
		string[0] = '-';
	if (n == 0)
		string[0] = '0';
	return (string);
}
