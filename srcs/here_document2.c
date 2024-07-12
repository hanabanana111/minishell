/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:00 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/12 15:20:00 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_here_doc_env_value(t_info *node, t_status *status)
{
	size_t				i;
	t_env_quote_info	e_q_info;

	i = 0;
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	while (node->str[i])
	{
		if (node->str[i] == '$')
		{
			treat_doll(&node->str[++i], &e_q_info);
			find_env(&e_q_info, status->envm);
			ft_chenge_env_to_value(node, &e_q_info);
		}
		i++;
	}
}

void	here_doc(t_info *cmd_info, t_status *status)
{
	t_info	*node;
	char	*eof;

	node = cmd_info;
	while (node)
	{
		if (node->type == LEFT && !ft_strncmp(node->str, "<<\0", 3)
			&& node->next)
		{
			eof = node->next->str;
			node->next->str = pipex_gnl(eof, status);
			node->next->str[s_strlen(node->next->str) - 1] = '\0';
			if (!node->next->is_quote)
				set_here_doc_env_value(node->next, status);
			free(eof);
		}
		node = node->next;
	}
}
