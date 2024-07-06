/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 06:08:51 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/06 10:37:22 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char **env, char *new)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	env[i] = new;
}

void	ft_cd(char **args, char **env)
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
	// change_old_pwd(env);
	change_pwd(env, new);
}
