/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:57:30 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 23:47:13 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim2(char *str, int index)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(str) - index + 1);
	if (ans == NULL)
		error_exit("ft_strtrim2");
	i = 0;
	while (str[index])
		ans[i++] = str[index++];
	ans[i] = '\0';
	free(str);
	return (ans);
}

void	ft_expjoin2(char *tmp, char *ans, int index, char *str)
{
	int	i;

	i = 0;
	while (tmp[i] != '"')
	{
		ans[i] = tmp[i];
		i++;
	}
	while (tmp[i + 1] != '"')
	{
		ans[i] = tmp[i + 1];
		i++;
	}
	index++;
	while (str[index])
		ans[i++] = str[index++];
	ans[i] = '\0';
}

int	check_eq2(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_expstr(char *tmp, char *tmp2)
{
	char	*ans;
	int		i;

	i = 0;
	ans = (char *)malloc(ft_strlen(tmp));
	while (tmp[i] != '+')
	{
		ans[i] = tmp[i];
		i++;
	}
	while (tmp[i + 1])
	{
		ans[i] = tmp[i + 1];
		i++;
	}
	ans[i] = '\0';
	printf("ans = %s\n", ans);
	free(tmp2);
	return (ans);
}
