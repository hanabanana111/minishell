/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:59:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/19 13:37:05 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwddup_2(void)
{
	char	*ans;
	char	tmp[PATH_MAX];
	int		i;

	if (getcwd(tmp, sizeof(tmp)) < 0)
		return (NULL);
	i = 0;
	while (tmp[i])
		i++;
	ans = (char *)malloc(i + 1);
	if (ans == NULL)
		return (NULL);
	i = -1;
	while (tmp[++i])
		ans[i] = tmp[i];
	ans[i] = '\0';
	return (ans);
}

int	check_pwd(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		if (ft_strncmp(exp[i], "declare -x PWD", 14) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	move_home2(t_status *status, char *old_path, char *path)
{
	if (!check_pwd(status->exp))
	{
		if (check_oldpwd(status->exp))
			change_oldpwd(status, old_path);
		free(status->pwd);
		status->pwd = ft_strdup(path);
		free(path);
		free(old_path);
		return (1);
	}
	if (check_oldpwd(status->exp))
		change_oldpwd(status, old_path);
	change_pwd(status, path);
	free(path);
	free(old_path);
	return (1);
}

int	ft_cd2(t_status *status, char *old_path, t_cmd *first)
{
	char	*path;

	if (old_path == NULL)
		return (1);
	if (check_pwd(status->exp))
		change_oldpwd(status, old_path);
	path = ft_pwddup_2();
	 if (!status->pwd)
			status->pwd = ft_strdup(first->arg[1]);
	change_pwd(status, path);
	free(old_path);
	free(path);
	return (1);
}

void	is_cd_too_many_args(void)
{
	ft_printf(2, "minishell: cd: too many arguments\n");
	end_status_func(1);
}
