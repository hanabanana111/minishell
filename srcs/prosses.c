/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/03 15:14:27 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *lst, char **env)
{
	
}

void	ft_miniprocess(t_info *lst, char **env)
{
	t_cmd	*info;

	info = create_lst(lst);
	info = path_finder(info, env);
	info = create_pipe(info, lst);
	ft_process(info, env);
}
