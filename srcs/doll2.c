/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:20 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/11 19:12:12 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_valid_env(size_t *count, const char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return ;
	if (ft_isdigit(str[i]) || ft_strchr("$", str[i]))
	{
		(*count)++;
		return ;
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && !ft_strchr("_",
				str[i]))
			break ;
		i++;
		(*count)++;
	}
}

int	is_doll(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
