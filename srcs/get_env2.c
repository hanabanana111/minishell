/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:35:47 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/14 00:19:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_home_path(char *pwd)
{
	size_t	i;
	size_t count;
	char *ret;
	char *tmp;
	
	i = 0;
	count = 0;
	if (!pwd)
		return (NULL);
	while(pwd[i])
	{
		if(pwd[i] == '/')
			count++;
		if (count == 3)
			break;
		i++;
	}
	tmp = (char *)ft_calloc(sizeof(char), i + 1);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, pwd, i + 1);
	ret = ft_strjoin("HOME=", tmp);
	free (tmp);
	return (ret);
}

char **set_env_if_null(void)
{
	char **ret;
	char *pwd;

	ret = (char **)ft_calloc(sizeof(char *), 5);
	if (!ret)
		return (NULL);
	pwd = ft_pwddup();
	ret[0] = ft_strjoin("PWD=", pwd);
	ret[1] = ft_strdup("SHLVL=1");
	ret[2] = ft_strdup("_=");
	ret[3] = get_home_path(pwd);
	free (pwd);
	return (ret);
}
