// Functions to calculate lenght

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	if (!s)
		return (0);
	ptr = s;
	while (*ptr)
	{
		ptr++;
	}
	return ((size_t)(ptr - s));
}

int	content_len(const char *str, va_list *args_p)
{
	int		count;
	char	*copy_str;
	va_list	copy_args;

	count = 0;
	va_copy(copy_args, *args_p);
	if (*str == 'c')
		count = 1;
	else if (*str == 's')
	{
		copy_str = va_arg(copy_args, char *);
		if (!copy_str)
			count += 6;
		count += ft_strlen(copy_str);
	}
	else if (*str == 'i' || *str == 'd')
		count = num_len(va_arg(copy_args, int));
	else if (*str == 'u')
		count = num_len((long long)va_arg(copy_args, unsigned int));
	else if (*str == 'p')
		count = point_len((uintptr_t)va_arg(copy_args, void *));
	else if (*str == 'x' || *str == 'X')
		count = hex_len((long long)va_arg(copy_args, unsigned int));
	va_end(copy_args);
	return (count);
}

int	point_len(uintptr_t point)
{
	int	len;

	len = 1;
	if (!point)
		return (5);
	while (point >= 16)
	{
		point = point / 16;
		len++;
	}
	return (len);
}

int	num_len(long long num)
{
	int	len;
	int	minus_flag;

	minus_flag = 0;
	len = 1;
	if (num < 0)
	{
		num = -num;
		minus_flag = 1;
	}
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len + minus_flag);
}

int	hex_len(long long num)
{
	int	len;
	int	minus_flag;

	minus_flag = 0;
	len = 1;
	if (num < 0)
	{
		num = num * -num;
		minus_flag = 1;
	}
	while (num >= 16)
	{
		num = num / 16;
		len++;
	}
	return (len + minus_flag);
}
