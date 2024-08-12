/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:20 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/11 19:05:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error_str(char *str)
{
	ft_printf(2, "minishell %s", str);
	return (2);
}

int	is_digits_all(t_cmd *lst)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (!lst->arg[1])
		return (TRUE);
	while (lst->arg[j])
	{
		i = 0;
		while (ft_isspace_tab_space(lst->arg[j][i]))
			i++;
		if (lst->arg[j][i] == '-' || lst->arg[j][i] == '+')
			i++;
		while (lst->arg[j][i])
		{
			if (!ft_isdigit(lst->arg[j][i])
				&& !is_space_till_end(&lst->arg[j][i]))
				return (FALSE);
			i++;
		}
		j++;
	}
	return (TRUE);
}

int	is_space_till_end(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_isspace_tab_space(int c)
{
	return (c == '\t' || c == ' ');
}
