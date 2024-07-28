/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:31:35 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/28 17:50:09 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_syntax2(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (is_syntax_error2(node))
			break ;
		node = node->next;
	}
}

int	is_here_document(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (is_syntax_error1_true_false(node))
			return (FALSE);
		if (node->type == LEFT && !ft_strncmp(node->str, "<<\0", 3))
		{
			if (node->next)
				return (TRUE);
		}
		node = node->next;
	}
	return (FALSE);
}

void	parser(t_info *cmd_info, t_status *status)
{
	if (!cmd_info)
		return ;
	status->is_redi_syntax = 0;
	status->is_pipe_syntax = 0;
	is_syntax1(cmd_info, status);
	here_doc_pipe(cmd_info, status);
	if (is_here_document(cmd_info))
		here_doc(cmd_info, status);
	if (!status->is_redi_syntax && !status->is_pipe_syntax)
		is_syntax2(cmd_info);
}
