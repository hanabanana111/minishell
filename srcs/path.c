/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:41:23 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/20 16:33:46 by hakobori         ###   ########.fr       */
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
	char	*ans;
	DIR		*fd;

	if (access(lst -> cmd, X_OK) < 0)
	{
		ans = ft_strdup(strerror(errno));
		if (ans == NULL)
			error_exit("path");
		return (ans);
	}
	fd = opendir(lst -> cmd);
	if (fd)
	{
		ans = ft_strdup("Is a directory\n");
		if (ans == NULL)
			error_exit("path");
		end_status_func(126);
		return (ans);
	}
	ans = ft_strdup(lst -> cmd);
	if (ans == NULL)
		error_exit("path");
	return (ans);
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
					lst -> path = ft_strdup("No such file or directory\0");
			}
			else if (lst -> cmd[0] == '\0')
				lst -> path = ft_strdup("command not found");
			else
				lst -> path = search_env(lst -> cmd, env);
		}
		lst = lst -> next;
	}
	return (ans);
}
