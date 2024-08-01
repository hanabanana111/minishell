/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/01 15:22:00 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pipe_exist(t_info *cmd_info)
{
	static int is_pipe;
	t_info *node;
	
	node = cmd_info;
	if (!cmd_info)
		return (is_pipe);
	if (cmd_info)
		is_pipe = 0;
	while(node)
	{
		if (node -> type == PIPE)
			is_pipe++;
		node = node -> next;
	}
	return (is_pipe);
}

void	is_line(t_status *status, t_info *cmd_info)
{
	add_history(status->line);
	cmd_info = lexer(status->line, status);
	if (!cmd_info)
		return ;
	parser(cmd_info, status);
	is_pipe_exist(cmd_info);
	if (!status->is_pipe_syntax && !status->is_redi_syntax && !g_sig)
		ft_miniprocess(cmd_info, status);
}

void	treat_read(t_status *status)
{
	t_info	*cmd_info;
	char	*pronpt;

	cmd_info = NULL;
	while (1)
	{
		pronpt = pronpt_ps1(status->envm);
		status->line = readline(pronpt);
		set_get_readline(status->line);
		free(pronpt);
		if (g_sig == SIGINT || g_sig == SIGQUIT)
		{
			g_sig = 0;
			if (g_sig == SIGINT)
				end_status_func(130);
			else if (g_sig == SIGQUIT)
				end_status_func(131);
		}
		if (!status->line)
			break ;
		else if (*status->line)
			is_line(status, cmd_info);
	}
	write(1, "exit\n", 5);
}
