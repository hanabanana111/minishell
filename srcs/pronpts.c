/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pronpts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:11:38 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 13:37:35 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pronpt_ps1(char **env)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PS1", 3))
		{
			ret = get_value(env,"PS1");
			if(ret[0] == '\0')
				break;
			return (ret);
		}
		i++;
	}
	ret = (char *)ft_calloc(13, sizeof(char));
	ft_strlcpy(ret, "minishell > ",13);
	return (ret);
}

char	*pronpt_ps2(char **env)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PS2", 3))
		{
			ret = get_value(env,"PS2");
			if(ret[0] == '\0')
				break;
			return (ret);
		}
		i++;
	}
	ret = (char *)ft_calloc(3, sizeof(char));
	ft_strlcpy(ret, "> ",3);
	return (ret);
}
