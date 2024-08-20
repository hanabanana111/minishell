/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:31 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/20 15:47:00 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_n(char *str)
{
	char	*opt;
	size_t	i;

	i = 0;
	if (!str)
		return (FALSE);
	opt = str;
	if (opt[0] == '-')
		i++;
	else
		return (FALSE);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	find_echo_part(char **arg)
{
	int	i;

	i = 1;
	while (arg[i] && check_option_n(arg[i]))
		i++;
	return (i);
}

void	echo_print_word_split(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	while (arg[i])
	{
		if (arg[i] == ' ' || arg[i] == '\t')
		{
			while (arg[i] == ' ' || arg[i] == '\t')
				i++;
			if (arg[i])
				ft_printf(1, " ");
			else
				break ;
		}
		ft_printf(1, "%c", arg[i]);
		i++;
	}
}

int	echo_func(t_cmd *lst)
{
	int	echo_part;
	int	i;

	echo_part = find_echo_part(lst->arg);
	if (!echo_part)
		return (1);
	i = echo_part;
	while (lst->arg[i])
	{
		echo_print_word_split(lst->arg[i]);
		if (!lst->arg[i + 1])
		{
			if (echo_part == 1)
				printf("\n");
			return (1);
		}
		ft_printf(1, " ");
		i++;
	}
	return (1);
}
