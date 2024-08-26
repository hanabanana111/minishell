/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/15 20:43:51 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe_cmd_lst_next(t_cmd **cmd_lst, int pp)
{
	(*cmd_lst)->next->pipe_0 = pp;
	(*cmd_lst) = (*cmd_lst)->next;
}

t_cmd	*create_pipe(t_cmd *ans, t_info *lst)
{
	t_cmd	*cmd_lst;
	// t_info	*first;
	int		pp[2];

	// first = lst;
	cmd_lst = ans;
	while (lst)
	{
		if (lst->type == LEFT)
			lst = infile_fd(cmd_lst, lst);
		else if (lst->type == RIGHT)
			lst = outfile_fd(cmd_lst, lst);
		if (lst->type == PIPE)
		{
			if (pipe(pp) < 0)
				return (free_cmd(ans), NULL);
			if (cmd_lst->pipe_1 == 1)
				cmd_lst->pipe_1 = pp[1];
			else
				close(pp[1]);
			set_pipe_cmd_lst_next(&cmd_lst, pp[0]);
		}
		lst = lst->next;
	}
	return (ans);
}
