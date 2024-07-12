/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_separate_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:23 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 20:18:23 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(char *cmd, char *str)
{
	char	cmd_c;
	int		i;

	i = 0;
	cmd_c = cmd[0];
	while (str[i])
	{
		if (cmd_c == '|' && i == 1)
			return (FALSE);
		if (str[i] != cmd_c || i == 2)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	separate_and_add_node(t_info *node, size_t i)
{
	char	*pre_str;
	t_info	*pre_node;
	t_info	*next_node;

	pre_str = node->str;
	pre_node = node;
	next_node = node->next;
	node->str = ft_strndup(pre_str, i);
	node->next = info_lstnew(&pre_str[i]);
	node->next->pre = pre_node;
	node->next->next = next_node;
	node->next->next->pre = node->next;
	free(pre_str);
}

void	separate_cmd(char *cmd, t_info *node, size_t *j)
{
	size_t	i;
	size_t	cmd_len;

	i = 0;
	cmd_len = s_strlen(cmd);
	while (node->str[i])
	{
		if (i == 0 && node->str[cmd_len] && !ft_strncmp(node->str, cmd,
				cmd_len))
		{
			if (check_cmd(cmd, node->str))
				break ;
			separate_and_add_node(node, cmd_len);
			(*j) = (*j) + cmd_len - 1;
			break ;
		}
		else if (i != 0 && !ft_strncmp(&node->str[i], cmd, cmd_len))
		{
			separate_and_add_node(node, i);
			break ;
		}
		i++;
	}
}

void	find_separater(t_info *node)
{
	size_t	i;

	i = 0;
	while (node->str[i])
	{
		if (!ft_strncmp(&node->str[i], "|", 1))
			separate_cmd("|", node, &i);
		else if (!ft_strncmp(&node->str[i], "<<", 2))
			separate_cmd("<<", node, &i);
		else if (!ft_strncmp(&node->str[i], "<", 1))
			separate_cmd("<", node, &i);
		else if (!ft_strncmp(&node->str[i], ">>", 2))
			separate_cmd(">>", node, &i);
		else if (!ft_strncmp(&node->str[i], ">", 1))
			separate_cmd(">", node, &i);
		i++;
	}
}

void	separator(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (node->str && !node->is_quote)
			find_separater(node);
		node = node->next;
	}
}
