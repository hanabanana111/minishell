/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:13:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/06 21:10:51 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_arr_to_lst(char **arr, t_info **cmd_lst)
{
	int		i;
	t_info	*node;

	i = 0;
	while (arr[i])
	{
		if (!*cmd_lst)
		{
			*cmd_lst = info_lstnew(arr[i]);
			node = *cmd_lst;
		}
		else
		{
			node->next = info_lstnew(arr[i]);
			node = node->next;
		}
		i++;
	}
}

void	count_quotes(char current_quote, t_env_quote_info *e_q_info)
{
	if (e_q_info->q_chr && e_q_info->q_chr != current_quote)
		return ;
	e_q_info->q_count++;
	e_q_info->q_chr = current_quote;
	if (e_q_info->q_count == 2)
	{
		e_q_info->q_count = 0;
		e_q_info->q_chr = 0;
	}
}

void	check_cmd_env(t_info *node, t_status *status)
{
	int					i;
	int					len;
	t_env_quote_info	e_q_info;

	i = 0;
	len = ft_strlen(node->str);
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	while (node->str[i])
	{
		if (node->str[i] == '$' && e_q_info.q_chr != '\'')
		{
			if (!ft_strchr(" \0", node->str[i + 1]) || node->str[i
				+ 1] != e_q_info.q_chr)
			{
				treat_doll(&node->str[++i], status, &e_q_info);
				find_env(&e_q_info, status);
				ft_chenge_env_to_value(node, &e_q_info);
			}
		}
		if (ft_strchr("\'\"", (node->str[i])))
			count_quotes(node->str[i], &e_q_info);
		i++;
	}
}

void	check_env(t_info *cmd_lst, t_status *status)
{
	t_info	*node;

	node = cmd_lst;
	while (node)
	{
		check_cmd_env(node, status);
		node = node->next;
	}
}

t_info	*treat_info_lst(char **arr, t_status *status)
{
	t_info	*cmd_lst;

	cmd_lst = NULL;
	set_arr_to_lst(arr, &cmd_lst);
	check_env(cmd_lst, status);
	format_quote(cmd_lst);
	return (cmd_lst);
}
