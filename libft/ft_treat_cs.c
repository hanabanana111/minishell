/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:58:59 by hakobori          #+#    #+#             */
/*   Updated: 2024/05/29 17:37:09 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treat_char(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_treat_string(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
