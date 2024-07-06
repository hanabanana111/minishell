/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 05:22:19 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/06 07:50:14 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_checker(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_len(char **args)
{
	int	ans;

	ans = 0;
	while (args[ans])
		ans++;
	return (ans);
}

void	echo_option(char **args)
{
	int	i;
	int	len;

	len = ft_len(args);
	i = 2;
	while (i < len - 1)
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (i == len - 1)
		ft_putstr_fd(args[i], 1);
}

void	echo_no_option(char **args)
{
	int	i;
	int	len;

	len = ft_len(args);
	i = 2;
	while (i < len - 1)
	{
		ft_putstr_fd(args[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (i == len - 1)
		ft_putstr_fd(args[i], 1);
	ft_putchar_fd('\n', 1);
}

void	ft_echo(char **args)
{
	char	*str;
	int		i;

	if (echo_checker(args[1]))
		echo_option(args);
	else
		echo_no_option(args);
}
