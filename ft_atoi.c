#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	str = advance_and_sign(str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

const char	*advance_and_sign(const char *str, int *sign)
{
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			*sign = -1;
		}
		str++;
	}
	return (str);
}
