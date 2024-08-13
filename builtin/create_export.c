/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:52:49 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/13 11:32:14 by hakobori         ###   ########.fr       */
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
		i++;
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
	while (exp[i] && ft_strcmp(exp[i], exp_str) < 0)
	{
		ans[i] = ft_strdup(exp[i]);
		i++;
	}
	ans[i] = exp_str;
	while (exp[i])
	{
		ans[i + 1] = ft_strdup(exp[i]);
		i++;
	}
	ans[i + 1] = NULL;
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
	if (exp == NULL)
		error_exit("create_exit");
	exp[0] = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) && ft_strncmp(env[i], "OLDPWD=", 7))
			exp = add_export(exp, env[i]);
		i++;
	}
	exp = add_export(exp, "OLDPWD");
	return (exp);
}
