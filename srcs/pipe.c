/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/04 13:36:28 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_pipe(t_cmd *cmd_lst, t_info *lst)
{
	t_cmd	*ans;
	int		pp[2];
	int		i;

	ans = lst;
	while (lst)
	{
		if (lst -> type == IN)
			lst = infile_fd(cmd_lst, lst);
		else if (lst -> type == OUT)
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
}
