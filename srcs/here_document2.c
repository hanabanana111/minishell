/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:19:00 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/10 20:53:03 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(int num)
{
	static int	is_heredoc_flg;

	if (num >= 0)
		is_heredoc_flg = num;
	return (is_heredoc_flg);
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
			treat_doll(&node->str[++i], &e_q_info, node);
			find_env(&e_q_info, status->envm);
			ft_chenge_env_to_value(node, &e_q_info);
		}
		i++;
	}
}

int	set_get_std_in(int fd)
{
	static int	std_in;

	if (fd >= 0)
		std_in = fd;
	else
		return (std_in);
	return (0);
}

void	here_doc(t_info *cmd_info, t_status *status)
{
	t_info	*node;
	char	*eof;
	int		fd;

	node = cmd_info;
	while (node)
	{
		if (node->type == LEFT && !ft_strncmp(node->str, "<<\0", 3)
			&& node->next)
		{
			eof = node->next->str;
			set_sigint_here_doc(SIGINT);
			node->next->str = pipex_gnl_rd(eof, status);
			fd = set_get_std_in(-1);
			dup2(fd, STDIN_FILENO);
			set_handler_sigint(SIGINT);
			if (node->next->str)
				node->next->str[s_strlen(node->next->str) - 1] = '\0';
			if (node->next && !node->next->is_quote)
				set_here_doc_env_value(node->next, status);
			free(eof);
		}
		node = node->next;
	}
}

