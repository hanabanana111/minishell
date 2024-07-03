/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:12:16 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/03 14:29:42 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin(char const *s1, char const *s2)
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

char	*relative_path(t_cmd *lst)
{
	char	tmp[PATH_MAX];
	char	*sl_cmd;
	char	*ab_path;

	if (getcwd(tmp, sizeof(tmp)) == NULL)
		perror("relative_path");
	ab_path = ft_strdup(tmp);
	ab_path = ft_strjoin(ab_path, lst -> cmd);
	if (access(ab_path, F_OK) < 0)
		return ("No such file or directory\0");
	return (ab_path);
}

char	slide_str(char *str)
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
	while (ft_strncmp(env[i], "PATH=", 5) && env[i])
		i++;
	if (env[i] == NULL)
		return ("Command not found\0");
	path = slide_str(env[i]);
	ans = ft_split(path, ':');
	if (ans == NULL)
	{
		free(path);
		write_error("split_path");
	}
	return (ans);
}

char	*search_env(char *cmd, char **env)
{
	int		i;
	char	**paths;

	paths = split_path(env);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	return ("Command not found\0");
}
