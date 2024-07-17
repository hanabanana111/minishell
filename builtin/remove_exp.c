/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:44:04 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 20:03:21 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exp(char **exp, char *str)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		ans;

	ans = -1;
	tmp = ft_strjoin("declare -x ", str);
	if (tmp == NULL)
		error_exit("check_exp");
	tmp2 = ft_strjoin(tmp, "=");
	if (tmp2 == NULL)
		error_exit("check_exp");
	i = 0;
	while (exp[i])
	{
		if (strncmp(exp[i], tmp, ft_strlen(tmp) + 1) == 0)
			ans = i;
		if (strncmp(exp[i], tmp2, ft_strlen(tmp2)) == 0)
			ans = i;
		i++;
	}
	free(tmp);
	free(tmp2);
	return (ans);
}

char	**remove_exp(char **exp, char *str)
{
	int		remove_index;
	char	**ans;
	int		i;
	int		l;

	i = -1;
	l = 0;
	remove_index = check_exp(exp, str);
	if (remove_index < 0)
		return (exp);
	ans = (char **)malloc(sizeof(char *) * ft_len(exp));
	if (ans == NULL)
		error_exit("remove_exp");
	while (exp[++i])
	{
		if (i != remove_index)
			ans[l++] = exp[i];
	}
	ans[l] = NULL;
	i = 0;
	while (exp[i])
		free(exp[i++]);
	free(exp[i]);
	free(exp);
	return (ans);
}
