/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/11 17:39:17 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	children_process(t_cmd *lst, char **env)
{
	if (dup2(lst -> pipe_0, 0) < 0 || dup2(lst -> pipe_1, 1) < 0)
		error_exit("children_process");
	if (lst -> pipe_0 != 0)
		close(lst -> pipe_0);
	if (lst -> pipe_1 != 1)
		close(lst -> pipe_1);
	if (execve(lst -> path, lst -> arg, env) < 0)
		re_process(lst, env);
}

void	parent_process(t_cmd *lst, int i)
{
	int	*end_status;

	end_status = (int *)malloc(sizeof(int));
	*end_status = 0;
	if (lst -> pipe_1 != 1)
		close(lst -> pipe_1);
	if (lst -> next == NULL)
	{
		while (i-- > 0)
		{
			waitpid(-1, end_status, 0);
			//はなさんの作ったエンドステータス関数へ
			//エンドステータス関数内でfree忘れない
		}
	}
}

void	ft_close(t_cmd *first)
{
	t_cmd	*lst;

	lst = first;
	while (lst)
	{
		close(lst -> pipe_0);
		lst = lst -> next;
	}
}