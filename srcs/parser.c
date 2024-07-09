/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 22:58:32 by hakobori         ###   ########.fr       */
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

int	is_syntax_error(t_info *node)
{
	if (node->type == 0 && !node->pre)
		return (show_syntax_error(node->str, node), TRUE);
	if (node->type == 1 || node->type == 2)
	{
		if (!node->next)
			return (show_syntax_error("newline", node), TRUE);
		if (node->type == 1 && node->next->type != OUT)
			return (show_syntax_error(node->next->str, node), TRUE);
		if (node->type == 2 && node->next->type != IN)
			return (show_syntax_error(node->next->str, node), TRUE);
	}
	return (FALSE);
}

void	is_syntax(t_syn_here *syn_here, t_info *cmd_info)
{
	t_info	*node;

	(void)syn_here;
	node = cmd_info;
	while (node)
	{
		if (is_syntax_error(node))
			break ;
		node = node->next;
	}
}

void	parser(t_info *cmd_info, t_status *status)
{
	t_syn_here	syn_here;

	ft_bzero(&syn_here, sizeof(t_syn_here));
	is_syntax(&syn_here, cmd_info);
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
		if (node->pre)
			printf("node->pre = %p\n", node->pre);
		if (node->is_quote)
			printf("node->is_quote = %d \n", node->is_quote);
		node = node->next;
	}
}
