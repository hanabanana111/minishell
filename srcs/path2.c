/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:12:16 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/19 13:06:31 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin3(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

char	*slide_str(char *str)
{
	char	*ans;
	int		i;

	i = 5;
	ans = (char *)malloc(ft_strlen(str) - 4);
	if (ans == NULL)
		error_exit("slide_str");
	while (str[i])
	{
		ans[i - 5] = str[i];
		i++;
	}
	ans[i - 5] = '\0';
	return (ans);
}

char	**split_path(char **env)
{
	char	**ans;
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (NULL);
	path = slide_str(env[i]);
	ans = ft_split(path, ':');
	if (ans == NULL)
	{
		free(path);
		error_exit("split_path");
	}
	free(path);
	return (ans);
}

char	*search_env2(char **paths, char *cmd)
{
	int		i;
	char	*ans;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin3(paths[i], "/");
		paths[i] = ft_strjoin3(paths[i], cmd);
		if (access(paths[i], R_OK) == 0)
		{
			ans = ft_strdup(paths[i]);
			if (ans == NULL)
				error_exit("search_env");
			ft_free_paths(i, paths);
			return (ans);
		}
		free(paths[i]);
		i++;
	}
	free(paths);
	ans = ft_strdup("command not found\0");
	if (ans == NULL)
		error_exit("serach_env");
	return (ans);
}

char	*search_env(char *cmd, char **env)
{
	char	**paths;
	char	*ans;

	paths = split_path(env);
	if (paths == NULL)
	{
		ans = ft_strjoin("./", cmd);
		if (access(ans, R_OK) == 0)
			return (ans);
		free(ans);
		ans = ft_strdup("command not found\0");
		if (ans == NULL)
			error_exit("serach_env");
		return (ans);
	}
	return (search_env2(paths, cmd));
}
