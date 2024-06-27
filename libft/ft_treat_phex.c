/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_phex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:58:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/05/29 17:37:02 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(unsigned long n, int fd, int *ret, char *base)
{
	unsigned int	base_len;

	base_len = (unsigned long)ft_strlen(base);
	if (n >= base_len)
		ft_putnbr_base_fd(n / base_len, fd, ret, base);
	ft_putchar_fd(*(base + (n % base_len)), fd);
	*ret += 1;
}

int	ft_treat_hex(unsigned int num, char c)
{
	int				ret;
	unsigned long	num2;

	num2 = (unsigned long)num;
	ret = 0;
	if (c == 'x')
		ft_putnbr_base_fd(num2, 1, &ret, HEX_LOWER_BASE);
	else if (c == 'X')
		ft_putnbr_base_fd(num2, 1, &ret, HEX_UPPER_BASE);
	return (ret);
}

int	ft_treat_p(void *p)
{
	int				ret;
	unsigned long	p2;

	p2 = (unsigned long)p;
	ft_putstr_fd("0x", 1);
	ret = 2;
	ft_putnbr_base_fd(p2, 1, &ret, HEX_LOWER_BASE);
	return (ret);
}
