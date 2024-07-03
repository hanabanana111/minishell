/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:41:23 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/03 13:31:55 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_sl(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            return (1);
    }
    return (0);
}

char	*absolute_path(t_cmd *lst)
{
	if (access(lst -> cmd, F_OK) < 0)
		return ("No such file or directory\0");
	else
		return (ft_strdup(lst -> cmd));
}

void	path_finder(t_cmd *lst, char **env)
{
	while (lst)
	{
		if (check_sl(lst -> cmd))
		{
			if (lst -> cmd[0] == '.')
				lst -> path = relative_path(lst);
			else if (lst -> cmd[0] = '/')
				lst -> path = absolute_path(lst);
			else
				lst -> path = "No such file or directory\0";
		}
		else
			lst -> path = search_env(lst -> cmd, env);
		lst = lst -> next;
	}
}
