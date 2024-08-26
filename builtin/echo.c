/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:31 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/26 23:36:53 by hakobori         ###   ########.fr       */
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

int	find_echo_part(t_cmd *lst, int *is_n)
{
	int	i;

	i = 1;
	while (lst->arg[i] && lst->arg[i][0] == '\0' && lst->flg[i])
		i++;
	while (lst->arg[i] && check_option_n(lst->arg[i]))
	{
		*is_n = 1;
		i++;
	}
	while (lst->arg[i] && lst->arg[i][0] == '\0' && lst->flg[i])
		i++;
	return (i);
}

int	echo_func(t_cmd *lst)
{
	int	echo_part;
	int	i;
	int	is_n;

	is_n = 0;
	echo_part = find_echo_part(lst, &is_n);
	if (!echo_part)
		return (1);
	i = echo_part;
	while (lst->arg[i])
	{
		printf("%s", lst->arg[i]);
		if (!lst->arg[i + 1])
			break ;
		printf(" ");
		i++;
	}
	if (!is_n)
		printf("\n");
	return (1);
}
