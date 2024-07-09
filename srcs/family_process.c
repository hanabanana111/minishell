/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/05 16:50:58 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children_process(t_cmd *lst, char **env, t_cmd *first, t_info *info_lst)
{
	if (dup2(lst -> pipe_0, 0) < 0 || dup2(lst -> pipe_1, 1) < 0)
		error_exit("children_process");
	close(lst -> pipe_0);
	close(lst -> pipe_1);
	if (execve(lst -> path, lst -> arg, env) < 0)
		re_process(lst, env, first, info_lst);
}

void	parent_process(t_cmd *lst, int i)
{
	close(lst -> pipe_1);
	if (lst -> next -> cmd == NULL)
	{
		while (i-- > 0)
			wait(NULL);
	}
}
