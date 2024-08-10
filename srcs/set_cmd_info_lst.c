/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:13:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/10 21:55:46 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_arr_to_lst(char **arr, t_info **cmd_lst)
{
	int		i;
	t_info	*node;
	t_info	*pre;

	i = 0;
	node = *cmd_lst;
	while (arr[i])
	{
		if (!*cmd_lst && i == 0)
		{
			*cmd_lst = info_lstnew(arr[i]);
			node = *cmd_lst;
		}
		else
		{
			pre = node;
			node->next = info_lstnew(arr[i]);
			node = node->next;
			node->pre = pre;
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

int	is_heredoc(t_info *node)
{
	size_t	i;

	i = 0;
	if (node->pre && !ft_strncmp(node->pre->str, "<<", 2))
		return (TRUE);
	else
	{
		while (node->str[i + 1])
		{
			if (!ft_strncmp(&node->str[i], "<<", 2))
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

void	check_cmd_env(t_info *node, char **envm)
{
	int					i;
	int					is_changed;
	t_env_quote_info	e_q_info;

	i = 0;
	is_changed = 0;
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	if (!node->str)
		return ;
	while (node->str && node->str[i])
	{
		if (!is_heredoc(node) && node->str[i] == '$' && e_q_info.q_chr != '\'')
		{
			if (node->str[i + 1] && !ft_strchr(" \0", node->str[i + 1])
				&& node->str[i + 1] != e_q_info.q_chr)
			{
				treat_doll(&node->str[++i], &e_q_info, node);
				find_env(&e_q_info, envm);
				ft_chenge_env_to_value(node, &e_q_info);
				i = ft_strlen(e_q_info.value);
				is_changed = 1;
			}
			if (!node->str[0] || !node->str[1])
			{
				free (e_q_info.key);
				e_q_info.key = NULL;
				break ;
			}
		}
		if (node->str[i] && ft_strchr("\'\"", (node->str[i])))
			count_quotes(node->str[i], &e_q_info);
		if(!is_changed)
			i++;
		is_changed = 0;
		if (node->key)
		{
			free(node->key);
			node->key =NULL;
		}
		free (e_q_info.key);
		e_q_info.key = NULL;
	}
}

void	check_env(t_info **cmd_lst, char **envm)
{
	t_info	*node;

	node = *cmd_lst;
	while (node)
	{
		check_cmd_env(node, envm);
		node = node->next;
	}
}
