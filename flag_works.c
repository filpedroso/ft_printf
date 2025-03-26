// Main logic for dealing with flags

#include "ft_printf.h"

void	flag_works(const char **str, va_list *args_p, int *count_p, int *cont_len)
{
	t_flags	flags;

	init_flags(&flags);
	parse_flags(str, &flags);
	if (!flags.has_flag)
		conv_work(str, args_p, count_p);
	else if (flags.conv == 'c')
		c_flag(args_p, count_p, flags);
	else if (flags.conv == 's')
		str_flag(args_p, count_p, flags, cont_len);
	else if (is_conversion(flags.conv))
	{
		if (flags.precision == 0)
		{
			*cont_len = 0;
			(*str)++;
			return ;
		}
		num_flag(args_p, count_p, flags, cont_len);
	}
	(*str)++;
}

void	c_flag(va_list *args_p, int *count_p, t_flags flags)
{
	if (!flags.l_just && flags.width)
	{
		*count_p += print_many(' ', flags.width - 1);
		*count_p += ft_printchar(va_arg(*args_p, int));
	}
	else if (flags.l_just && flags.width)
	{
		*count_p += ft_printchar(va_arg(*args_p, int));
		*count_p += print_many(' ', flags.width - 1);
	}
	else
		*count_p += ft_printchar(va_arg(*args_p, int));
}

void	str_flag(va_list *args_p, int *count_p, t_flags flags, int *cont_len)
{
	int	trim;

	trim = 0;
	if (flags.precision >= 0 && *cont_len > flags.precision)
		trim = *cont_len - flags.precision;
	if (!flags.l_just && (flags.width > *cont_len))
	{
		*count_p += print_many(' ', (flags.width - *cont_len) + trim);
		*count_p += ft_printstr(va_arg(*args_p, char *), trim);
	}
	else if (flags.l_just && (flags.width > *cont_len))
	{
		*count_p += ft_printstr(va_arg(*args_p, char *), trim);
		*count_p += print_many(' ', (flags.width - *cont_len) + trim);
	}
	else
		*count_p += ft_printstr(va_arg(*args_p, char *), trim);
	*cont_len -= trim;
}

void	parse_flags(const char **format, t_flags *flags)
{
	while (**format && (ft_isdigit(**format) || is_flag(**format)))
	{
		flags->has_flag = 1;
		if (**format == '-')
		{
			flags->l_just = 1;
			flags->zero_pad = 0;
		}
		else if (**format == '0' && flags->width == 0 && flags->l_just == 0)
			flags->zero_pad = '0';
		else if (**format == '.')
		{
			flags->precision = ft_atoi(*format + 1);
			if (flags->precision)
				*format += num_len(flags->precision);
		}
		else if (ft_isdigit(**format) && flags->precision == -1)
		{
			flags->width = ft_atoi(*format);
			*format += -1 + num_len(flags->width);
		}
		(*format)++;
	}
	if (is_conversion(**format))
		flags->conv = **format;
}

void	conv_work(const char **str, va_list *args_p, int *count_p)
{
	long	ptr_n;

	if (is_conversion(**str))
	{
		if (**str == 'c')
			*count_p += ft_printchar(va_arg(*args_p, int));
		else if (**str == 's')
			*count_p += ft_printstr(va_arg(*args_p, char *), 0);
		else if (**str == 'i' || **str == 'd')
			*count_p += ft_printnbr(va_arg(*args_p, int));
		else if (**str == 'u')
			*count_p += ft_printnbr(va_arg(*args_p, unsigned int));
		else if (**str == 'p')
		{
			ptr_n = (uintptr_t)va_arg(*args_p, void *);
			*count_p += printnbr_hub((long)ptr_n, 'p') + 2;
			if (!ptr_n)
				*count_p -= 2;
		}
		else if (**str == 'x' || **str == 'X')
			*count_p += print_hex((uintptr_t)va_arg(*args_p, unsigned int), 0,
					**str);
	}
}

// Logic for number-related flags

void	num_flag(va_list *args_p, int *count_p, t_flags flags, int *cont_len)
{
	long	num;

	num = 0;
	if (flags.conv == 'i' || flags.conv == 'd')
	{
		num = va_arg(*args_p, int);
		if (num < 0)
		{
			*count_p += ft_printchar('-');
			num = -num;
			if (flags.precision > 0)
				*cont_len -= 1;
		}
	}
	else if (flags.conv == 'u' || flags.conv == 'X' || flags.conv == 'x')
		num = va_arg(*args_p, unsigned int);
	else if (flags.conv == 'p')
	{
		num = (long)(uintptr_t)va_arg(*args_p, void *);
		flags.precision = -1;
		*cont_len += 2;
		*count_p += 2;
	}
	num_flag_help(count_p, flags, cont_len, num);
}

void	num_flag_help(int *count_p, t_flags flags, int *cont_len, long num)
{
	if (flags.conv == 'p' && !num)
	{
		*cont_len -= 2;
		*count_p -= 2;
	}
	if (!flags.l_just)
	{
		if (flags.precision > *cont_len)
		{
			if (flags.precision > flags.width)
				*count_p += print_many('0', (flags.precision - *cont_len));
			else
			{
				*count_p += print_many(' ', (flags.width - flags.precision));
				*count_p += print_many('0', (flags.precision - *cont_len));
			}
		}
		else if (flags.width > *cont_len)
			*count_p += print_many(flags.zero_pad, (flags.width - *cont_len));
		*count_p += printnbr_hub(num, flags.conv);
	}
	else if (flags.l_just)
		num_flag_left(count_p, flags, cont_len, num);
}

void	num_flag_left(int *count_p, t_flags flags, int *cont_len, long num)
{
	if (flags.precision > *cont_len)
	{
		*count_p += print_many('0', (flags.precision - *cont_len));
		*count_p += printnbr_hub(num, flags.conv);
		if (flags.width > flags.precision)
			*count_p += print_many(' ', (flags.width - flags.precision));
	}
	else
	{
		*count_p += printnbr_hub(num, flags.conv);
		if (flags.width > *cont_len)
			*count_p += print_many(' ', (flags.width - *cont_len));
	}
}

void	init_flags(t_flags *flags)
{
	flags->has_flag = 0;
	flags->l_just = 0;
	flags->zero_pad = ' ';
	flags->precision = -1;
	flags->width = 0;
	flags->conv = '\0';
}
