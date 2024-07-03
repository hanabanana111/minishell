/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:46:28 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/03 15:12:27 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_pipe(t_cmd *cmd_lst, t_info *lst)
{
	t_cmd	*ans;
	int		pp[2];
	int		i;

	ans = cmd_lst;
	while (lst)
	{
		if (lst -> type == IN)
			cmd_lst -> pipe_0 = determine_infile(lst -> str, lst -> next -> str);
		else if (lst -> type == OUT)
			cmd_lst -> pipe_1 = determine_outfile(lst -> str, lst -> next -> str);
		else if (lst -> type == PIPE)
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
