/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:43:55 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/15 17:05:29 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	waitpid_set_endstatus(void)
{
	int		end_status;

	waitpid(-1, &end_status, 0);
	if (WIFEXITED(end_status))
		end_status_func(WEXITSTATUS(end_status));
	else if (WIFSIGNALED(end_status))
		end_status_func(128 + WTERMSIG(end_status));
}

void	process_sig(t_cmd *cmd_lst)
{
	if (is_minishell(cmd_lst->path))
		sig_ign_all();
	else
		sig_status_all();
}

void	fork_and_process(t_cmd *first, t_cmd *cmd_lst, t_status *env, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		children_process(cmd_lst, env, first);
	else if (pid > 0)
		parent_process(cmd_lst, i);
}
