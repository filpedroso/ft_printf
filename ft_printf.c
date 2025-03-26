// Main function's entry point

#include "ft_printf.h"

int	ft_printf(const char *fstr, ...)
{
	int		count;
	int		fstr_len;
	va_list	args;
	int		cont_len;

	if (!fstr)
		return (-1);
	fstr_len = 0;
	cont_len = 0;
	count = 0;
	va_start(args, fstr);
	while (*fstr)
	{
		if (*fstr == '%')
			cont_len += percent_work(&fstr, &args, &count, &fstr_len);
		else
		{
			count += ft_printchar(*fstr++);
			fstr_len++;
		}
	}
	va_end(args);
	if (count < (cont_len + fstr_len))
		return (-1);
	return (count);
}

int	percent_work(const char **str, va_list *args_p, int *count_p, int *fstr_len)
{
	int			cont_len;
	const char	*copy_s;

	cont_len = 0;
	while (**str == '%' && *(*str + 1) == '%')
	{
		*count_p += ft_printchar('%');
		*str += 2;
		(*fstr_len)++;
		return (cont_len);
	}
	if (**str == '%')
		(*str)++;
	copy_s = *str;
	while (!is_conversion(*copy_s))
		copy_s++;
	cont_len = content_len(copy_s, args_p);
	flag_works(str, args_p, count_p, &cont_len);
	return (cont_len);
}
