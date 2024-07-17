/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:42:22 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 20:40:43 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	len;

	len = ft_strlen(str1);
	if (len < ft_strlen(str2))
		len = ft_strlen(str2);
	return (ft_strncmp(str1, str2, len + 1));
}

char	*expdup2(char *ans, char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] != '=')
	{
		ans[i] = tmp[i];
		i++;
	}
	ans[i] = tmp[i];
	i++;
	ans[i++] = '"';
	while (tmp[i - 1])
	{
		ans[i] = tmp[i - 1];
		i++;
	}
	ans[i++] = '"';
	ans[i] = '\0';
	free(tmp);
	return (ans);
}
