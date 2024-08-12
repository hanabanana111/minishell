/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/12 20:40:51 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_pipe(t_cmd *ans, t_info *lst)
{
	t_cmd	*cmd_lst;
	 t_info *first;
	int		pp[2];

	first = lst;
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
			cmd_lst->next->pipe_0 = pp[0];
			cmd_lst = cmd_lst->next;
		}
		lst = lst->next;
	}
	return (ans);
}
