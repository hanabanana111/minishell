/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/17 19:33:02 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	children_process(t_cmd *lst, t_status *env_lst)
{
	if (lst -> pipe_0 != 0)
	{
		if (dup2(lst -> pipe_0, 0) < 0)
		{
			close(lst -> pipe_0);
			error_exit("children_process");
		}
		close(lst -> pipe_0);
	}
	if (lst -> pipe_1 != 1)
	{
		if (dup2(lst -> pipe_1, 1) < 0)
		{
			close(lst -> pipe_1);
			error_exit("children_process");
		}
		close(lst -> pipe_1);
	}
	if (built_in(lst, env_lst))
		exit(0);
	if (execve(lst -> path, lst -> arg, env_lst -> envm) < 0)
		re_process(lst, env_lst);
}

void	parent_process(t_cmd *lst, int i)
{
	int	end_status;

	end_status = 0;
	if (lst -> pipe_1 != 1)
		close(lst -> pipe_1);
	if (lst -> next == NULL)
	{
		while (i-- > 0)
		{
			waitpid(-1, &end_status, 0);
			end_status_func(end_status);
		}
	}
}

void	ft_close(t_cmd *first)
{
	t_cmd	*lst;

	lst = first;
	while (lst)
	{
		if (lst -> pipe_0)
			close(lst -> pipe_0);
		lst = lst -> next;
	}
}
