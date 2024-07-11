/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/11 16:51:43 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_pipe(t_cmd *ans, t_info *lst)
{
	t_cmd	*cmd_lst;
	int		pp[2];

	cmd_lst = ans;
	while (lst)
	{
		if (lst -> type == LEFT)
			lst = infile_fd(cmd_lst, lst);
		else if (lst -> type == RIGHT)
			lst = outfile_fd(cmd_lst, lst);
		if (lst -> type == PIPE)
		{
			if (pipe(pp) < 0)
				error_exit("create_pipe");
			if (cmd_lst -> pipe_1 == 1)
				cmd_lst -> pipe_1 = pp[1];
			else
				close(pp[1]);
			cmd_lst -> next -> pipe_0 = pp[0];
			cmd_lst = cmd_lst -> next;
		}
		lst = lst -> next;
	}
	return (ans);
}
