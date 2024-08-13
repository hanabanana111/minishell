/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:31:40 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/13 10:08:48 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_exist(char **env, char *str)
{
	int		i;
	char	*env_str;

	i = 0;
	env_str = ft_strjoin(str, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], env_str, ft_strlen(env_str)) == 0)
		{
			free(env_str);
			return(1);
		}
		i++;
	}
	free(env_str);
	return (0);
}

int	unset_func(t_status *status, t_cmd *first)
{
	int	i;

	if (ft_lstlen(first) > 1)
		return (0);
	i = 1;
	while (first -> arg[i])
	{
		if (ft_strncmp(first -> arg[i], "_\0", 2))
		{
			status -> exp = remove_exp(status -> exp, first -> arg[i]);
			if (check_env_exist(status -> envm, first -> arg[i]))
				status -> envm = remove_env(status -> envm, first -> arg[i]);
		}
		i++;
	}
	return (1);
}
