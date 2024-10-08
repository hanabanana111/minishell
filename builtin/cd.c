/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:02:40 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/27 01:21:42 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_home_path(char *str, t_status *status)
{
	char	*ans;
	int		i;
	int		l;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (ft_strdup(status->pwd));
	ans = (char *)malloc(ft_strlen(str) - 4);
	if (ans == NULL)
		error_exit("ft_home_path");
	l = 0;
	while (str[++i])
		ans[l++] = str[i];
	ans[l] = '\0';
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

int	move_home(char **env, t_status *status, t_cmd *lst)
{
	char	*path;
	char	*old_path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "HOME", 4))
		i++;
	if (env[i] == NULL)
		return (printf_error_cd3(lst));
	path = ft_home_path(env[i], status);
	old_path = ft_strdup(status->pwd);
	if (ft_strlen(path) == 0)
		return (free(path), free(old_path), 1);
	if (chdir(path) < 0)
	{
		free(old_path);
		return (printf_error_cd2(path, lst));
	}
	return (move_home2(status, old_path, path));
}

int	ft_cd(t_cmd *first, t_status *status)
{
	char	*old_path;

	if (ft_lstlen(first) > 1)
		return (0);
	if (first->arg[1] == NULL)
		return (move_home(status->envm, status, first));
	if (ft_strncmp(first->arg[1], "\0", 1) == 0)
		return (1);
	if (first->arg[2])
		return (is_cd_too_many_args(), 1);
	if (ft_strncmp(first->arg[1], ".\0", 2) == 0)
		return (1);
	first->arg = replace_home(first->arg, status);
	if (ft_strncmp(first->arg[1], "..\0", 3) == 0)
		first->arg[1] = re_pwd(status, first->arg[1]);
	if (chdir(first->arg[1]) < 0)
		return (printf_error_cd(first));
	old_path = ft_strdup(status->pwd);
	return (ft_cd2(status, old_path, first));
}
