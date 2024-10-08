/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pronpts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:11:38 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/13 11:16:09 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pronpt_ps1(char **env)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PS1=", 4) && env[i][4])
		{
			ret = get_value(env, "PS1");
			if (ret[0] == '\0')
				break ;
			return (ret);
		}
		i++;
	}
	ret = (char *)ft_calloc(13, sizeof(char));
	ft_strlcpy(ret, "minishell > \0", 13);
	return (ret);
}

char	*pronpt_ps2(char **env)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PS2=", 4))
		{
			ret = get_value(env, "PS2");
			if (ret[0] == '\0')
				break ;
			return (ret);
		}
		i++;
	}
	ret = (char *)ft_calloc(4, sizeof(char));
	ft_strlcpy(ret, "> ", 3);
	return (ret);
}
