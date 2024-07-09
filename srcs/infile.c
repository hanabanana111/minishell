/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/04 15:47:49 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirect1(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	return (fd);
}

int	infile_redirect2(char *str)
{
	int		pipe_fd[2];
	size_t	byte;

	if (pipe(pipe_fd) < 0)
		error_exit("infile_redirect");
	byte = write(pipe_fd[1], str, ft_strlen(str) + 1);
	if (byte < 0)
		error_exit("infile_redirect");
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	determine_infile(char *cmd, char *next)
{
	if (ft_strncmp(cmd, "<<\0", 3) == 0)
		return (infile_redirect2(next));
	else if (ft_strncmp(cmd, "<\0", 2) == 0)
		return (infile_redirect1(next));
}

t_info	*infile_fd(t_cmd *cmd_lst, t_info *lst)
{
	cmd_lst -> pipe_0 = determine_infile(lst -> str, lst -> next -> str);
	if (cmd_lst -> pipe_0 < 0)
	{
		cmd_lst -> pipe_0 = errno;
		cmd_lst -> error_file = ft_strdup(lst -> next -> str);
		while (lst -> next -> type != PIPE && lst -> next)
			lst = lst -> next;
	}
	return (lst);
}
