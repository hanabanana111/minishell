/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:01:23 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/25 17:40:12 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	children_process(t_cmd *lst, t_status *env_lst)
{
	treat_signal();
	if (lst->pipe_0 != 0)
	{
		if (dup2(lst->pipe_0, 0) < 0)
		{
			close(lst->pipe_0);
			error_exit("children_process");
		}
		close(lst->pipe_0);
	}
	if (lst->pipe_1 != 1)
	{
		if (dup2(lst->pipe_1, 1) < 0)
		{
			close(lst->pipe_1);
			error_exit("children_process");
		}
		close(lst->pipe_1);
	}
	if (built_in(lst, env_lst))
		exit(0);
	is_execve(1);
	if (execve(lst->path, lst->arg, env_lst->envm) < 0)
		re_process(lst, env_lst);
	is_execve(1);
}

void	parent_process(t_cmd *lst, int i)
{
	int	end_status;

	end_status = 0;
	if (lst->pipe_1 != 1)
		close(lst->pipe_1);
	if (lst->next == NULL)
	{
		while (i-- > 0)
		{
			waitpid(-1, &end_status, 0);
			if (WIFEXITED(end_status))
				end_status_func(WEXITSTATUS(end_status));
			else if (WIFSIGNALED(end_status))
				end_status_func(WEXITSTATUS(end_status));
			write(1, "\n", 1);
			treat_signal();
		}
	}
}

void	ft_close(t_cmd *first)
{
	t_cmd	*lst;

	lst = first;
	while (lst)
	{
		if (lst->pipe_0)
			close(lst->pipe_0);
		lst = lst->next;
	}
}
