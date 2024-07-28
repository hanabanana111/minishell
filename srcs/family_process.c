/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/28 18:29:06 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	children_process(t_cmd *lst, t_status *env_lst, t_cmd *first)
{
	if(!is_minishell(lst->path))
	{
		set_handler_sigquit(SIGQUIT);
		set_handler_sigint(SIGINT);
	}
	if (lst->pipe_0 != 0)
		dup2(lst->pipe_0, 0);
	if (lst->pipe_1 != 1)
		dup2(lst->pipe_1, 1);
	ft_close(first);
	if (built_in(lst, env_lst))
		exit(0);
	if (execve(lst->path, lst->arg, env_lst->envm) < 0)
		re_process(lst, env_lst);
}

void	parent_process(t_cmd *lst, int i)
{
	int	end_status;

	end_status = 0;
	if (lst->pipe_1 != 1)
		close(lst->pipe_1);
	if (lst->pipe_0 > 2)
		close(lst -> pipe_0);
	if (lst->next == NULL)
	{
		while (i-- > 0)
		{
			waitpid(-1, &end_status, 0);
			if (WIFEXITED(end_status))
				end_status_func(WEXITSTATUS(end_status));
			treat_signal();
		}
	}
}

void	ft_close(t_cmd *lst)
{
	while (lst)
	{
		if (lst -> pipe_0 > 2)
			close(lst -> pipe_0);
		if (lst -> pipe_1 > 2)
			close(lst -> pipe_1);
		lst = lst -> next;
	}
}
