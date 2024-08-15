/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:10:54 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/15 15:06:19 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	outfile_redirect1(char *outfile)
{
	int	fd;

	if (ft_strlen(outfile) == 0)
		return (-2);
	fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	return (fd);
}

int	outfile_redirect2(char *outfile)
{
	int	fd;

	if (ft_strlen(outfile) == 0)
		return (-2);
	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	return (fd);
}

int	determine_outfile(char *cmd, char *next)
{
	if (ft_strncmp(cmd, ">>\0", 3) == 0)
		return (outfile_redirect2(next));
	else if (ft_strncmp(cmd, ">\0", 2) == 0)
		return (outfile_redirect1(next));
	return (1);
}

void	ambiguous_outfile(t_cmd *cmd_lst, t_info *lst)
{
	if (lst->next->key)
	{
		cmd_lst->error_file = ft_strjoin(lst->next->key, ": ");
		if (cmd_lst->error_file == NULL)
			error_exit("outfile_fd");
		cmd_lst->error_file = ft_strjoin2(cmd_lst->error_file,
				"ambiguous redirect");
		if (cmd_lst->error_file == NULL)
			error_exit("outfile_fd");
	}
	else
	{
		cmd_lst->error_file = ft_strjoin(lst->next->key, ": ");
		if (cmd_lst->error_file == NULL)
			error_exit("outfile_fd");
		cmd_lst->error_file = ft_strjoin2(cmd_lst->error_file,
				"No such file or directory");
		if (cmd_lst->error_file == NULL)
			error_exit("outfile_fd");
	}
}

t_info	*outfile_fd(t_cmd *cmd_lst, t_info *lst)
{
	char	*e_str;

	if (cmd_lst->pipe_1 != 1)
		close(cmd_lst->pipe_1);
	cmd_lst->pipe_1 = determine_outfile(lst->str, lst->next->str);
	if (cmd_lst->pipe_1 < 0)
	{
		if (cmd_lst->pipe_1 == -2)
			ambiguous_outfile(cmd_lst, lst);
		else
		{
			cmd_lst->error_file = ft_strjoin(lst->next->str, ": ");
			if (cmd_lst->error_file == NULL)
				error_exit("outfile_fd");
			e_str = strerror(errno);
			cmd_lst->error_file = ft_strjoin2(cmd_lst->error_file, e_str);
			if (cmd_lst->error_file == NULL)
				error_exit("outfile_fd");
		}
		while (lst->next && lst->next->type != PIPE)
			lst = lst->next;
	}
	return (lst);
}
