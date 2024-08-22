/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:31 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/22 19:14:37 by rkawahar         ###   ########.fr       */
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

int	find_echo_part(t_cmd *lst)
{
	int	i;

	i = 1;
	while (lst->arg[i] && lst->arg[i][0] == '\0' && lst->flg[i])
		i++;
	while (lst->arg[i] && check_option_n(lst->arg[i]))
		i++;
	return (i);
}

int	echo_func(t_cmd *lst)
{
	int	echo_part;
	int	i;

	echo_part = find_echo_part(lst);
	if (!echo_part)
		return (1);
	i = echo_part;
	while (lst->arg[i])
	{
		printf("%s", lst->arg[i]);
		if (!lst->arg[i + 1])
		{
			if (echo_part == 1)
				printf("\n");
			return (1);
		}
		printf(" ");
		i++;
	}
	return (1);
}
