/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:41:23 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/11 16:34:42 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_sl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*path(t_cmd *lst)
{
	if (access(lst -> cmd, X_OK) < 0)
		return (strerror(errno));
	else
		return (ft_strdup(lst -> cmd));
}

t_cmd	*path_finder(t_cmd *ans, char **env)
{
	t_cmd	*lst;

	lst = ans;
	while (lst)
	{
		if (lst -> cmd)
		{
			if (check_sl(lst -> cmd))
			{
				if (lst -> cmd[0] == '/' || lst -> cmd[0] == '.')
					lst -> path = path(lst);
				else
					lst -> path = "No such file or directory\0";
			}
			else
				lst -> path = search_env(lst -> cmd, env);
		}
		lst = lst -> next;
	}
	return (ans);
}
