/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:54:54 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/07 18:18:13 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_len(char **env)
{
	int	ans;

	ans = 0;
	while (env[ans])
		ans++;
	return (ans);
}

int	sort_system(char **env, char *str)
{
	int	ans;
	int	i;

	ans = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], str) < 0)
			ans++;
		i++;
	}
	return (ans);
}

char	*include_dqt(char *str)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(str) + 3);
	i = 0;
	while (str[i] != '=')
	{
		ans[i] == str[i];
		i++;
	}
	ans[i] = str[i];
	ans[++i] = '"';
	i++;
	while (str[i - 1])
	{
		ans[i] = str[i - 1];
		i++;
	}
	ans[i++] = '"';
	ans[i] = '\0';
	free(str);
	return (ans);
}

char	*export_str(char *str)
{
	char	*ans;

	ans = ft_strjoin("declare -x ", str);
	ans = include_dqt(ans);
	return (ans);
}

char	**create_export(char **env)
{
	int		i;
	int		index;
	char	**ans;

	i = ft_len(env);
	ans = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2))
		{
			index = sort_system(env, env[i]);
			ans[index] = export_str(env[i]);
		}
		i++;
	}
	ans[ft_len(env) - 1] = NULL;
	ans = add_export(ans, "OLDPWD");
	return (ans);
}
