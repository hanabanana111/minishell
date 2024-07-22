/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:53:44 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/22 20:20:36 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
	}
	return (0);
}

int	env_func(char **env, t_cmd *lst)
{
	size_t	i;

	i = 0;
	if (check_env_path(env) == 0)
		return (printf("env: No such file or directory\n"));
	if (lst->pre || lst->next)
		return (0);
	if (!env || !env[i])
	{
		printf("\n");
		return (0);
	}
	while (env[i])
		printf("%s\n", env[i++]);
	return (1);
}
