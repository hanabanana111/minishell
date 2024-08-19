/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/19 13:36:22 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd_exist(char *path, t_cmd *lst)
{
	if (check_builtin(lst->cmd))
		return (1);
	if (path != NULL && access(path, X_OK) == 0)
		return (1);
	if (lst->pipe_0 > 0)
	{
		close(lst->pipe_0);
		end_status_func(1);
	}
	if (lst->pipe_1 > 1)
	{
		close(lst->pipe_1);
		end_status_func(1);
	}
	if (lst->error_str || lst->cmd)
	{
		if (lst->error_str)
			ft_printf(2, "%s: ", lst->error_str);
		else
			ft_printf(2, "minishell: ");
		end_status_func(127);
	}
	if (lst->cmd)
		ft_printf(2, "%s: %s\n", lst->cmd, lst->path);
	return (0);
}

int	check_fd(int pipe_0, int pipe_1, t_cmd *lst)
{
	if (pipe_0 < 0)
	{
		if (lst->error_str)
			ft_printf(2, "%s: ", lst->error_str);
		else
			ft_printf(2, "minishell: ");
		ft_printf(2, "%s\n", lst->error_file);
		if (pipe_1 > 1)
			close(pipe_1);
		end_status_func(1);
		return (0);
	}
	if (pipe_1 < 0)
	{
		if (lst->error_str)
			ft_printf(2, "%s: ", lst->error_str);
		else
			ft_printf(2, "minishell: ");
		ft_printf(2, "%s\n", lst->error_file);
		if (pipe_0 > 0)
			close(pipe_0);
		end_status_func(1);
		return (0);
	}
	return (1);
}

void	ft_process(t_cmd *first, t_status *env)
{
	int		i;
	t_cmd	*cmd_lst;

	i = 0;
	cmd_lst = first;
	while (cmd_lst)
	{
		if (check_fd(cmd_lst->pipe_0, cmd_lst->pipe_1, cmd_lst))
		{
			if (check_cmd_exist(cmd_lst->path, cmd_lst))
			{
				i++;
				process_sig(cmd_lst);
				fork_and_process(first, cmd_lst, env, i);
			}
		}
		cmd_lst = cmd_lst->next;
	}
	while (i-- > 0)
		waitpid_set_endstatus();
	treat_signal();
}

t_cmd	*check_cmdlst(t_cmd *first)
{
	t_cmd	*lst;
	int		i;

	lst = first;
	while (lst)
	{
		i = 0;
		printf("--------------------------------\n");
		printf("cmd = %s\n", lst->cmd);
		while (lst->arg[i])
		{
			printf("arg[%d] = %s\n", i, lst->arg[i]);
			i++;
		}
		printf("path = %s\n", lst->path);
		printf("pipe_0 = %d\n", lst->pipe_0);
		printf("pipe_1 = %d\n", lst->pipe_1);
		printf("error_file = %s\n", lst->error_file);
		printf("error_str = %s\n", lst->error_str);
		lst = lst->next;
	}
	return (first);
}

void	ft_miniprocess(t_info *first, t_status *env_lst)
{
	t_cmd	*info;
	t_info	*lst;
	t_cmd	*cmd_first;

	lst = first;
	info = create_lst(lst);
	info = path_finder(info, env_lst->envm);
	lst = first;
	info = create_pipe(info, lst);
	if (info == NULL)
		return ;
	if (ft_strncmp(lst -> str, "\0", 1) == 0 && lst -> key && !(lst -> next))
		return ;
	cmd_first = info;
	if (builtin2(cmd_first, env_lst))
	{
		free_cmd(info);
		return ;
	}
	ft_process(info, env_lst);
	free_cmd(info);
}
