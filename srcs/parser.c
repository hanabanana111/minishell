/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/26 18:47:25 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_syntax_error(char *str, t_info *node)
{
	char	*head;

	if (node->flg)
		head = node->errstr;
	else
		head = ft_strdup("minishell");
	printf("%s: syntax error near unexpected token `%s'\n", head, str);
	end_status_func(2);
	if (!node->flg)
		free(head);
	if (node->flg)
		exit(1);
}

int	is_syntax_error1(t_info *node, t_status *status)
{
	if (node->type == 0 && !node->pre)
	{
		status->is_redi_syntax = 1;
		return (show_syntax_error(node->str, node), TRUE);
	}
	if (node->type == 0 && node->next && node->next->type == 0)
	{
		status->is_redi_syntax = 1;
		return (show_syntax_error(node->next->str, node), TRUE);
	}
	if (node->type == 1 || node->type == 2)
	{
		if (!node->next)
			return (FALSE);
		if (node->type == 1 && node->next->type != OUT)
			status->is_redi_syntax = 1;
		if (node->type == 2 && node->next->type != IN)
			status->is_redi_syntax = 1;
		if (node->type == 1 && node->next->type != OUT)
			return (show_syntax_error(node->next->str, node), TRUE);
		if (node->type == 2 && node->next->type != IN)
			return (show_syntax_error(node->next->str, node), TRUE);
	}
	return (FALSE);
}

int	is_syntax_error1_true_false(t_info *node)
{
	if (node->type == 0 && !node->pre)
		return (TRUE);
	if (node->type == 0 && node->next && node->next->type == 0)
		return (TRUE);
	if (node->type == 1 || node->type == 2)
	{
		if (!node->next)
			return (FALSE);
		if (node->type == 1 && node->next->type != OUT)
			return (TRUE);
		if (node->type == 2 && node->next->type != IN)
			return (TRUE);
	}
	return (FALSE);
}

void	is_syntax1(t_info *cmd_info, t_status *status)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (is_syntax_error1(node, status))
		{
			if (node->type == 0 && node->next && node->next->type == 0)
				status->is_pipe_syntax = 1;
			break ;
		}
		node = node->next;
	}
}

int	is_syntax_error2(t_info *node)
{
	if (node->type == 1 || node->type == 2)
	{
		if (!node->next)
			return (show_syntax_error("newline", node), TRUE);
	}
	return (FALSE);
}
