/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pronpts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:11:38 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 22:52:34 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pronpt(char **env)
{
	size_t	i;
	char	*ret;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PS1", 3))
			return (get_ps1_value(env[i]));
	}
	ret = (char *)ft_calloc(12, sizeof(char));
	ft_strlcpy(ret, "minishell >");
	return (ret);
}
