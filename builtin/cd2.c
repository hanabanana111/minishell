/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:38:45 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/13 09:54:20 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_env(char **env, char *key)
{
	char	**ans;
	size_t	len;
	char	*env_str;
	int		i;
	int		l;

	len = ft_len(env);
	env_str = ft_strjoin(key, "=");
	ans = (char **)ft_calloc(sizeof(char *), len);
	if (ans == NULL)
		error_exit("remove_env");
	i = 0;
	l = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env_str, ft_strlen(env_str)))
			ans[l++] = ft_strdup(env[i]);
		i++;
	}
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	free(env_str);
	return (ans);
}

void	change_oldpwd(t_status *status, char *old_path)
{
	char	*str;

	str = ft_strjoin("OLDPWD=\0", old_path);
	if (str == NULL)
		error_exit("change_oldpwd");
	if (old_path)
		add_env(status, str);
	status -> exp = remove_exp(status -> exp, "OLDPWD");
	status -> exp = add_export(status -> exp, str);
	free(str);
}

void	change_pwd(t_status *status, char *path)
{
	char	*str;

	str = ft_strjoin("PWD=\0", path);
	if (str == NULL)
		error_exit("change_pwd");
	add_env(status, str);
	status->exp = remove_exp(status->exp, "PWD");
	status->exp = add_export(status->exp, str);
	free(status->pwd);
	status->pwd = ft_strdup(path);
	free(str);
}

char	*cd_strjoin(char *arg, char *home)
{
	char	*ans;
	int		i;
	int		l;

	ans = (char *)malloc(ft_strlen(arg) + ft_strlen(home) + 1);
	if (ans == NULL)
		error_exit("cd_strjoin");
	i = -1;
	while (home[++i])
		ans[i] = home[i];
	l = 0;
	while (arg[++l])
		ans[i++] = arg[l];
	ans[i] = '\0';
	return (ans);
}

char	**replace_home(char **arg, t_status *status)
{
	char	**ans;
	int		i;

	ans = (char **)malloc(sizeof(char *) * (ft_len(arg) + 1));
	if (ans == NULL)
		error_exit("replace_home");
	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '~')
			ans[i] = cd_strjoin(arg[i], status->home);
		else
			ans[i] = ft_strdup(arg[i]);
		if (ans[i] == NULL)
			error_exit("replace_home");
		i++;
	}
	ans[i] = NULL;
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg[i]);
	free(arg);
	return (ans);
}
