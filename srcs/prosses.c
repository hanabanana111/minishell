/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/11 21:10:42 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_cmd_exist(char *path, t_cmd *lst)
{
	if (access(path, X_OK) == 0)
		return (1);
	if (lst -> pipe_0 > 0)
		close(lst -> pipe_0);
	if (lst -> pipe_1 > 1)
		close(lst -> pipe_1);
	if (lst -> error_str)
		printf("%s: ", lst -> error_str);
	if (lst -> cmd)
		printf("%s: %s\n", lst -> cmd, lst -> path);
	return (0);
}

int	check_fd(int pipe_0, int pipe_1, t_cmd *lst)
{
	if (pipe_0 < 0)
	{
		if (lst -> error_str)
			printf("%s: ", lst -> error_str);
		printf("%s\n", lst -> error_file);
		if (pipe_1 > 1)
			close(pipe_1);
		return (0);
	}
	if (pipe_1 < 0)
	{
		if (lst -> error_str)
			printf("%s: ", lst -> error_str);
		printf("%s\n", lst -> error_file);
		if (pipe_0 > 0)
			close(pipe_0);
		return (0);
	}
	return (1);
}

void	ft_process(t_cmd *first, t_status *env)
{
	pid_t	pid;
	int		i;
	t_cmd	*cmd_lst;

	i = 0;
	cmd_lst = first;
	while (cmd_lst)
	{
		if (check_fd(cmd_lst -> pipe_0, cmd_lst -> pipe_1, cmd_lst))
		{
			if (check_cmd_exist(cmd_lst -> path, cmd_lst))
			{
				i++;
				pid = fork();
				if (pid == 0)
					children_process(cmd_lst, env);
				else if (pid > 0)
					parent_process(cmd_lst, i);
			}
		}
		cmd_lst = cmd_lst -> next;
	}
	ft_close(first);
}

t_cmd *check_cmdlst(t_cmd *first)
{
	t_cmd	*lst;
	int		i;

	lst = first;
	while (lst)
	{
		i = 0;
		printf("--------------------------------\n");
		printf("cmd = %s\n", lst -> cmd);
		while (lst -> arg[i])
		{
			printf("arg[%d] = %s\n", i, lst -> arg[i]);
			i++;
		}
		printf("path = %s\n", lst -> path);
		printf("pipe_0 = %d\n", lst -> pipe_0);
		printf("pipe_1 = %d\n", lst -> pipe_1);
		printf("error_file = %s\n", lst -> error_file);
		printf("error_str = %s\n", lst -> error_str);
		lst = lst -> next;
	}
	return (first);
}

void	ft_miniprocess(t_info *first, t_status *env_lst)
{
	t_cmd	*info;
	t_info	*lst;

	lst = first;
	info = create_lst(lst);
	info = path_finder(info, env_lst -> envm);
	lst = first;
	info = create_pipe(info, lst);
	// info = check_cmdlst(info);
	ft_process(info, env_lst);
	// printf("ft_miniprocess was passed\n");
}
