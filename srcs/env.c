/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:45:53 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/08 13:59:32 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env(char *str, char **env)
{
	int		i;
	char	**ans;

	i = 0;
	while (env[i])
		i++;
	ans = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		ans[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	ans[i++] = str;
	ans[i] = NULL;
	return (ans);
}
