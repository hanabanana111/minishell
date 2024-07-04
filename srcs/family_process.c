/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/04 17:16:41 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	children_process(t_cmd *lst, char **env)
{
	if (dup2(lst -> pipe_0, 0) < 0 || dup2(lst -> pipe_1, 1) < 0)
		error_exit("children_process");
	close(lst -> pipe_0);
	close(lst -> pipe_1);
	if (execve(lst -> path, lst -> arg, env) < 0)
		re_process(lst);
	
}
