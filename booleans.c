// Booleans for identifying types

#include "ft_printf.h"

int	is_conversion(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X');
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	is_flag(char c)
{
	return (ft_isdigit(c) || c == '-' || c == '.' || c == '0');
}
