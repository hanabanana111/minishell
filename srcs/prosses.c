/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/03 16:45:54 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *cmd_lst, t_info *lst, char **env)
{
	pid_t	pid;

	while (cmd_lst)
	{
		
		cmd_lst = cmd_lst -> next;
	}
}

void	ft_miniprocess(t_info *lst, char **env)
{
	t_cmd	*info;

	info = create_lst(lst);
	info = path_finder(info, env);
	// info = create_pipe(info, lst);
	ft_process(info, lst, env);
}
