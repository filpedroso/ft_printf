// Headers

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>


typedef struct s_flags
{
	int		has_flag;
	int		l_just;
	int		zero_pad;
	int		precision;
	int		width;
	char	conv;
}			t_flags;

// ft_printf.c
int	ft_printf(const char *str, ...) __attribute__((format(printf, 1, 2)));
int	percent_work(const char **str, va_list *args_p, int *count_p, int *fstr_len);

// flag_works.c
void	flag_works(const char **str, va_list *args_p, int *count_p, int *cont_len);
void	c_flag(va_list *args_p, int *count_p, t_flags flags);
void	str_flag(va_list *args_p, int *count_p, t_flags flags, int *cont_len);
void	parse_flags(const char **format, t_flags *flags);
void	conv_work(const char **str, va_list *args_p, int *count_p);
void	num_flag(va_list *args_p, int *count_p, t_flags flags, int *cont_len);
void	num_flag_help(int *count_p, t_flags flags, int *cont_len, long num);
void	num_flag_left(int *count_p, t_flags flags, int *cont_len, long num);
void	init_flags(t_flags *flags);

// len_count_tools.c
size_t	ft_strlen(const char *s);
int		content_len(const char *str, va_list *args_p);
int		point_len(uintptr_t point);
int		num_len(long long num);
int		hex_len(long long num);

// printing_tools.c
int		ft_printchar(char c);
int		ft_printstr(char *s, int trim);
int		printnbr_hub(long num, char conv_type);
int		print_many(char c, int amount);
int		ft_printnbr(long n);
void	deli_rec(long long num, int *count);
int		print_hex(uintptr_t num, int counter, char upper);

// ft_atoi.c
int	ft_atoi(const char *str);
const char	*advance_and_sign(const char *str, int *sign);

// booleans.c
int	is_conversion(char c);
int	ft_isdigit(int c);
int	ft_isascii(int c);
int	is_flag(char c);

#endif