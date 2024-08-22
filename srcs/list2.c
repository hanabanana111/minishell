/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:29:44 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/22 20:11:02 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_arg(char *str1, t_info *lst)
{
	while (lst)
	{
		if (lst -> str && ft_strncmp(str1, lst -> str, ft_strlen(str1) + 1) == 0)
			break ;
		lst = lst -> next;
	}
	if (lst -> key)
	{
		free(lst -> str);
		lst -> str = strdup("NULL");
		return (1);
	}
	return (0);
}

t_cmd	*insert_flg(t_info *lst, t_cmd *ans)
{
	t_cmd	*cmd_lst;
	int		i;

	cmd_lst = ans;
	i = 0;
	while (cmd_lst)
	{
		while (cmd_lst -> arg[i])
			i++;
		cmd_lst -> flg = (int *)ft_calloc(sizeof(int), i);
		if (cmd_lst -> flg == NULL)
			error_exit("insert_flg");
		i = 0;
		while (cmd_lst -> arg[i])
		{
			cmd_lst -> flg[i] = search_arg(cmd_lst -> arg[i], lst);
			i++;
		}
		cmd_lst = cmd_lst -> next;
	}
	return (ans);
}
