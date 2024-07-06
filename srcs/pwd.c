/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 07:42:26 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/06 09:39:47 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*slide_str(char *str)
{
	char	*ans;
	int		i;

	i = 0;
	ans = (char *)malloc(ft_strlen(str) - 3);
	while (str[i + 4])
	{
		ans[i] = str[i + 4];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

void	ft_pwd(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	pwd = slide_str(env[i]);
	printf("%s\n", pwd);
	free(pwd);
}
