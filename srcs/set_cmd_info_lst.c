/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:13:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/15 15:34:00 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_cmd_env_part1(t_info *node, int *i, char **envm,
		t_env_quote_info *e_q_info)
{
	treat_doll(&node->str[++(*i)], e_q_info, node);
	find_env(e_q_info, envm);
	ft_chenge_env_to_value(node, e_q_info);
	(*i) = ft_strlen(e_q_info->value);
	e_q_info->is_changed = 1;
}

void	check_cmd_env_part2(t_info *node, int *i, t_env_quote_info *e_q_info)
{
	if (!e_q_info->is_changed)
		(*i)++;
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	free(e_q_info->key);
	e_q_info->key = NULL;
}

void	check_cmd_env(t_info *node, char **envm)
{
	int					i;
	t_env_quote_info	e_q_info;

	i = 0;
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	if (!node->str)
		return ;
	while (node->str && node->str[i])
	{
		e_q_info.is_changed = 0;
		if (!is_heredoc(node) && node->str[i] == '$' && e_q_info.q_chr != '\'')
		{
			if (node->str[i + 1] && !ft_strchr(" \0", node->str[i + 1])
				&& node->str[i + 1] != e_q_info.q_chr)
				check_cmd_env_part1(node, &i, envm, &e_q_info);
			if (!node->str[0] || !node->str[1])
				break ;
		}
		if (node->str[i] && ft_strchr("\'\"", (node->str[i])))
			count_quotes(node->str[i], &e_q_info);
		check_cmd_env_part2(node, &i, &e_q_info);
	}
}
