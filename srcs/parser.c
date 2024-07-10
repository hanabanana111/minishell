/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/10 17:18:10 by hakobori         ###   ########.fr       */
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
	if (!node->flg)
		free(head);
	if (node->flg)
		exit(1);
}

int	is_syntax_error1(t_info *node)
{
	if (node->type == 0 && !node->pre)
		return (show_syntax_error(node->str, node), TRUE);
	if (node->type == 0 && node->next && node->next->type == 0)
		return (show_syntax_error(node->next->str, node), TRUE);
	if (node->type == 1 || node->type == 2)
	{
		if (!node->next)
			return (FALSE);
		if (node->type == 1 && node->next->type != OUT)
			return (show_syntax_error(node->next->str, node), TRUE);
		if (node->type == 2 && node->next->type != IN)
			return (show_syntax_error(node->next->str, node), TRUE);
	}
	return (FALSE);
}

void	is_syntax1(t_info *cmd_info,t_status *status)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (is_syntax_error1(node))
		{
			if(node->type == 0 && node->next && node->next->type == 0)
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
		// if (node->type == 1 && node->next->type != OUT)
		// 	return (show_syntax_error(node->next->str, node), TRUE);
		// if (node->type == 2 && node->next->type != IN)
		// 	return (show_syntax_error(node->next->str, node), TRUE);
	}
	return (FALSE);
}

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

int is_here_document(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (node->type == LEFT && !ft_strncmp(node->str,"<<\0",3) && node->next)
			return(TRUE);
		node = node->next;
	}
	return(FALSE);
}

// int is_here_document_for_pipe()
// {
	
// }

void	parser(t_info *cmd_info, t_status *status)
{
	// t_syn_here	syn_here;

	// ft_bzero(&syn_here, sizeof(t_syn_here));
	is_syntax1(cmd_info,status);
	here_doc_pipe(cmd_info,status);
	if(is_here_document(cmd_info))
		here_doc(cmd_info,status);
	is_syntax2(cmd_info);
	(void)status;
	(void)cmd_info;
}

void	debug_print_lst(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		printf("cmd = %s\n", node->str);
		printf("type = %d\n", node->type);
		// if (node->pre)
		// 	printf("node->pre = %p\n", node->pre);
		if (node->is_quote)
			printf("node->is_quote = %d \n", node->is_quote);
		node = node->next;
	}
}
