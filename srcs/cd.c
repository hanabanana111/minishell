/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:08:51 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/07 18:48:23 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char **env, char *new, char **export)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	env[i] = new;
}

void	change_old_pwd(char **env, char *export)
{
	int		i;
	char	*old_pwd;
	char	*export_oldpwd;

	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	old_pwd = ft_strjoin("OLD", env[i]);
	i = 0;
	while (ft_strncmp("OLDPWD", env[i], 6) && env[i])
		i++;
	if (env[i])
	{
		free(env[i]);
		env[i] = old_pwd;
	}
	else
		env = add_env(old_pwd, env);
	export_oldpwd = export_str(old_pwd);
	
}

void	ft_cd(char **args, char **env, char **export)
{
	char	buf[PATH_MAX];
	int		len;
	int		i;
	char	*new;

	if (chdir(args[1]) < 0)
	{
		printf("%s: %s: ", args[0], args[1]);
		perror(NULL);
	}
	getcwd(buf, sizeof(buf));
	len = ft_strlen(buf);
	new = (char *)malloc(len + 5);
	ft_strlcpy(new, "PWD=", 4);
	i = 4;
	while (buf[i - 4])
	{
		new[i] = buf[i - 4];
		i++;
	}
	new[i] = '\0';
	change_old_pwd(env, export);
	change_pwd(env, new, export);
}
