/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:00 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/24 22:52:13 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_here_doc(int num)
{
	static int is_heredoc_flg;

	if(num >= 0)
		is_heredoc_flg = num;
	return(is_heredoc_flg);
}

void	set_here_doc_env_value(t_info *node, t_status *status)
{
	size_t				i;
	t_env_quote_info	e_q_info;

	i = 0;
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	while (node && node->str && node->str[i])
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
			is_here_doc(1);
			node->next->str = pipex_gnl_rd(eof, status);
			is_here_doc(0);
			if(node->next->str)
				node->next->str[s_strlen(node->next->str) - 1] = '\0';
			if (node->next && !node->next->is_quote)
				set_here_doc_env_value(node->next, status);
			free(eof);
		}
		node = node->next;
	}
}
