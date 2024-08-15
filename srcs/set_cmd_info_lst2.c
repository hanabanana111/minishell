/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:18:58 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/15 15:18:51 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
