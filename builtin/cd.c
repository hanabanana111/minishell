/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:02:40 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/22 12:34:54 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_home_path(char *str)
{
	char	*ans;
	int		i;
	int		l;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
	{
		ans = (char *)malloc(2);
		if (ans == NULL)
			error_exit("ft_home_path");
		ft_strlcpy(ans, ".\0", 2);
		return (ans);
	}
	ans = (char *)malloc(ft_strlen(str) - 4);
	if (ans == NULL)
		error_exit("ft_home_path");
	l = 0;
	while (str[++i])
		ans[l++] = str[i];
	ans[i] = '\0';
	return (ans);
}

char	*ft_old_path(char **env)
{
	int		i;
	int		l;
	char	*ans;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i] == NULL)
		return (NULL);
	ans = (char *)malloc(ft_strlen(env[i]) - 3);
	if (ans == NULL)
		error_exit("ft_old_path");
	l = 0;
	while (env[i][l] != '=')
		l++;
	while (env[i][++l])
		ans[l - 4] = env[i][l];
	ans[l - 4] = '\0';
	return (ans);
}
int	check_oldpwd(char **exp)
{
	int	i;

	i = 0;
	while (exp[i] && ft_strncmp(exp[i], "declare -x OLDPWD", 17))
		i++;
	if (exp[i])
		return (1);
	return (0);
}

int	move_home(char **env, t_status *status)
{
	char	*path;
	char	*old_path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME", 4))
		i++;
	if (env[i] == NULL)
		return (printf("cd: HOME not set\n"));
	path = ft_home_path(env[i]);
	old_path = ft_old_path(env);
	if (chdir(path) < 0)
	{
		free(path);
		free(old_path);
		return (printf("cd: %s: %s\n", path, strerror(errno)));
	}
	if (old_path == NULL)
		return (1);
	if (check_oldpwd(status -> exp))
		change_oldpwd(status, old_path);
	change_pwd(status, path);
	free(path);
	free(old_path);
	return (1);
}

int	ft_cd(t_cmd *first, t_status *status)
{
	char	*old_path;

	if (ft_lstlen(first) > 1)
		return (0);
	if (first -> arg[1] == NULL)
		return (move_home(status -> envm, status));
	first -> arg = replace_home(first -> arg, status);
	if (chdir(first -> arg[1]) < 0)
		return (printf("minishell: cd: %s: %s\n", first -> arg[1], strerror(errno)));
	old_path = ft_old_path(status -> envm);
	if (old_path == NULL)
		return (1);
	if (check_oldpwd(status -> exp))
		change_oldpwd(status, old_path);
	change_pwd(status, first -> arg[1]);
	free(old_path);
	return (1);
}
