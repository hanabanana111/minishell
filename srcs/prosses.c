/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/04 17:07:55 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_exist(char *path, t_cmd *lst)
{
	if (access(path, X_OK) == 0)
		return (1);
	close(lst -> pipe_0);
	close(lst -> pipe_1);
	perror(lst -> cmd);
	return (0);
}

int	check_fd(int pipe_0, int pipe_1, t_cmd *lst)
{
	if (pipe_0 < 0)
	{
		ft_printf("%s: %s\n", lst -> error_file, strerror(lst -> pipe_0));
		if (pipe_1 > 1)
			close(pipe_1);
		return (0);
	}
	if (pipe_1 < 0)
	{
		printf("%s: %s\n", lst -> error_file, strerror(lst -> pipe_1));
		if (pipe_0 > 0)
			close(pipe_0);
		return (0);
	}
	return (1);
}

void	ft_process(t_cmd *cmd_lst, t_info *lst, char **env)
{
	pid_t	pid;

	while (cmd_lst)
	{
		if (check_fd(cmd_lst -> pipe_0, cmd_lst -> pipe_1, cmd_lst))
		{
			if (check_cmd_exist(cmd_lst -> path, cmd_lst))
			{
				pid = fork();
				if (pid == 0)
					children_process(cmd_lst, env);
				else if (pid > 0)
					parent_process();
			}
		}
		cmd_lst = cmd_lst -> next;
	}
}

void	ft_miniprocess(t_info *lst, char **env)
{
	t_cmd	*info;

	info = create_lst(lst);
	info = path_finder(info, env);
	info = create_pipe(info, lst);
	ft_process(info, lst, env);
}
