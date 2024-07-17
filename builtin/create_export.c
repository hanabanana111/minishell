/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:52:49 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 19:58:09 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
	}
	return (1);
}

char	*expdup(char *str)
{
	char	*ans;
	char	*tmp;

	tmp = ft_strjoin("declare -x ", str);
	if (tmp == NULL)
		error_exit("expdup");
	if (check_eq(tmp))
		return (tmp);
	ans = (char *)malloc(ft_strlen(tmp) + 3);
	if (ans == NULL)
		error_exit("expdup");
	return (expdup2(ans, tmp));
}

int	ft_len(char **exp)
{
	int	ans;

	ans = 0;
	while (exp[ans])
		ans++;
	return (ans);
}

char	**add_export(char **exp, char *str)
{
	char	**ans;
	int		i;
	char	*exp_str;

	ans = (char **)malloc(sizeof(char *) * (ft_len(exp) + 2));
	exp_str = expdup(str);
	i = 0;
	while (exp[i] && ft_strcmp(exp[i], str) < 0)
	{
		ans[i] = ft_strdup(exp[i]);
		i++;
	}
	ans[i++] = exp_str;
	while (exp[i - 1])
	{
		ans[i] = exp[i - 1];
		i++;
	}
	ans[i] = NULL;
	i = 0;
	while (exp[i])
		free(exp[i++]);
	free(exp[i]);
	free(exp);
	return (ans);
}

char	**create_export(char **env)
{
	char	**exp;
	int		i;

	exp = (char **)malloc(sizeof(char *));
	exp = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=/usr/bin/env\0", 15))
			exp = add_export(exp, env[i]);
		i++;
	}
	exp = add_export(exp, "OLDPWD");
	return (exp);
}
