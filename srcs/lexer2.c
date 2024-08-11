/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:27:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/11 19:01:19 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_separater_n(t_info *node, size_t *i)
{
	if (!ft_strncmp(&node->str[*i], "|", 1))
		separate_cmd("|", node, i);
	else if (!ft_strncmp(&node->str[*i], "<<", 2))
		separate_cmd("<<", node, i);
	else if (!ft_strncmp(&node->str[*i], "<", 1))
		separate_cmd("<", node, i);
	else if (!ft_strncmp(&node->str[*i], ">>", 2))
		separate_cmd(">>", node, i);
	else if (!ft_strncmp(&node->str[*i], ">", 1))
		separate_cmd(">", node, i);
}

void	is_redi_pipe_next_to_quotes(t_info *node)
{
	char	*tmp;
	size_t	i;
	char	q_char;

	i = 0;
	q_char = 0;
	tmp = node->str;
	while (tmp[i])
	{
		if (!q_char && ft_strchr("\\<\\|\\>", tmp[i]))
			find_separater_n(node, &i);
		if (ft_strchr("\'\"", tmp[i]))
		{
			if (!q_char)
				q_char = tmp[i];
			else if (q_char == tmp[i])
				q_char = 0;
		}
		i++;
	}
	if (ft_strncmp(tmp, node->str, ft_strlen(node->str)))
		free(tmp);
}

void	separate_outsize_of_qoute(t_info **cmd_info)
{
	t_info	*node;

	node = *cmd_info;
	while (node)
	{
		if (node->str)
			is_redi_pipe_next_to_quotes(node);
		node = node->next;
	}
}

void	set_lst_details(t_info **cmd_info, char **envm)
{
	check_env(cmd_info, envm);
	separate_outsize_of_qoute(cmd_info);
	format_quote(cmd_info);
	separator(cmd_info);
	set_token_types(cmd_info);
}

t_info	*lexer(char *line, t_status *status)
{
	char	**arr;
	t_info	*cmd_info;

	arr = split_to_token(line, " \t\n");
	if (!arr)
		return (NULL);
	cmd_info = NULL;
	set_arr_to_lst(arr, &cmd_info);
	ft_free_2d_array(arr);
	set_lst_details(&cmd_info, status->envm);
	return (cmd_info);
}
