/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:39:54 by hakobori          #+#    #+#             */
/*   Updated: 2024/05/17 15:53:51 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_treat_smt(char *str, va_list args)
{
	int	ret;

	ret = 0;
	str++;
	if (!(*str))
		ret = 0;
	else if (*str == 'c')
		ret = ft_treat_char(va_arg(args, int));
	else if (*str == 's')
		ret = ft_treat_string(va_arg(args, char *));
	else if (*str == 'p')
		ret = ft_treat_p(va_arg(args, void *));
	else if (*str == 'd' || *str == 'i')
		ret = ft_trest_di(va_arg(args, int));
	else if (*str == 'u')
		ret = ft_treat_u(va_arg(args, unsigned int));
	else if (*str == 'x' || *str == 'X')
		ret = ft_treat_hex(va_arg(args, unsigned int), *str);
	else if (*str == '%')
		ret = ft_treat_char('%');
	else
		ret = ft_treat_char(*str);
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		ret;
	char	*str;

	str = (char *)fmt;
	if (!*str)
		return (0);
	ret = 0;
	va_start(ap, fmt);
	while (*str)
	{
		if (*str == '%')
			ret += ft_treat_smt(str++, ap);
		else
		{
			ft_putchar_fd(*str, 1);
			ret++;
		}
		if (*str)
			str++;
	}
	va_end(ap);
	return (ret);
}

// #include<stdio.h>

// int	main(void)
// {
// 	int num;
// 	char *str="";
// 	// int num2;

// 	num = printf("%p\n",str);
// 	printf("ans len = %d\n\n", num);
// 	num = ft_printf("%p\n",str);
// 	ft_printf("res len = %d\n", num);
// 	// ft_printf("res len = %d\n", num2);
// 	// num = 16;
// 	// printf("%d\n", ft_get_digits(num));
// }
