/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:15:21 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/07 18:26:33 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(s1, s2)
{
	size_t	i;

	i = ft_strlen(s1);
	if (i < ft_strlen(s2))
		i = ft_strlen(s2);
	return (ft_strncmp(s1, s2, i));
}

char	**add_export(char **exp, char *str)
{
	char	*exp_str;
	int		i;
	char	*tmp;

	exp_str = ft_strjoin("declare -x ", str);
	while (ft_strcmp(exp[i], exp_str) < 0)
		i++;
	while (exp_str)
	{
		tmp = exp[i];
		exp[i] = exp_str;
		exp_str = tmp;
		i++;
	}
	exp[i] = exp_str;
	return (exp);
}