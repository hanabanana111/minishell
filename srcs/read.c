/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/18 06:21:24 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_exist(t_info *cmd_info)
{
	static int	is_pipe;
	t_info		*node;

	node = cmd_info;
	if (!cmd_info)
		return (is_pipe);
	if (cmd_info)
		is_pipe = 0;
	while (node)
	{
		if (node->type == PIPE)
			is_pipe++;
		node = node->next;
	}
	return (is_pipe);
}

void	free_t_info(t_info **cmd_info)
{
	t_info	*node;
	t_info	*tmp;

	node = *cmd_info;
	if (!*cmd_info)
		return ;
	while (node)
	{
		tmp = node;
		free(node->str);
		free(node->key);
		free(node->errstr);
		node = node->next;
		free(tmp);
	}
}

void	is_line(t_status *status, t_info **cmd_info)
{
	if (!ft_strncmp(status->line, "\0", 1))
		return ;
	else
		add_history(status->line);
	*cmd_info = lexer(status->line, status);
	if (!*cmd_info)
		return ;
	if (!parser(*cmd_info, status))
		return ;
	is_pipe_exist(*cmd_info);
	if (!status->is_pipe_syntax && !status->is_redi_syntax && !g_sig)
		ft_miniprocess(*cmd_info, status);
}

void	treat_read(t_status *status)
{
	t_info	*cmd_info;
	char	*pronpt;

	pronpt = NULL;
	while (1)
	{
		cmd_info = NULL;
		pronpt = pronpt_ps1(status->envm);
		status->line = readline(pronpt);
		free(pronpt);
		if (g_sig)
			g_sig = 0;
		if (!status->line)
			break ;
		else if (status->line)
		{
			is_line(status, &cmd_info);
			free_t_info(&cmd_info);
		}
		free(status->line);
	}
	write(1, "exit\n", 5);
}
