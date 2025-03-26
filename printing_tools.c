// Tools for writing different formats to terminal

#include "ft_printf.h"

int	ft_printchar(char c)
{
	int	i;

	i = write(1, &c, 1);
	return (i);
}

int	ft_printstr(char *s, int trim)
{
	size_t	buffer;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (s[0] == '\0')
		return (0);
	buffer = ft_strlen(s);
	return (write(1, s, buffer - trim));
}

int	printnbr_hub(long num, char conv_type)
{
	if (conv_type == 'i' || conv_type == 'd' || conv_type == 'u')
		return (ft_printnbr(num));
	if (conv_type == 'x' || conv_type == 'X')
		return (print_hex((uintptr_t)num, 0, conv_type));
	if (conv_type == 'p')
	{
		if (!num)
			return (ft_printstr("(nil)", 0));
		ft_printstr("0x", 0);
		return (print_hex((uintptr_t)num, 0, conv_type));
	}
	else
		return (0);
}

int	print_many(char c, int amount)
{
	int	count;

	if (amount <= 0)
		return (0);
	count = 0;
	while (amount)
	{
		count += write(1, &c, 1);
		amount--;
	}
	return (count);
}

int	ft_printnbr(long n)
{
	long long	num;
	int			count;

	num = n;
	count = 0;
	if (num < 0)
	{
		num = -num;
		ft_printchar('-');
		count++;
	}
	deli_rec(num, &count);
	return (count);
}

void	deli_rec(long long num, int *count)
{
	if (num >= 10)
		deli_rec(num / 10, count);
	(*count) += ft_printchar(num % 10 + '0');
}

int	print_hex(uintptr_t num, int counter, char upper)
{
	if (num >= 16)
		counter = print_hex(num / 16, counter, upper);
	if (upper == 'X')
		counter += ft_printchar("0123456789ABCDEF"[num % 16]);
	else
		counter += ft_printchar("0123456789abcdef"[num % 16]);
	return (counter);
}
