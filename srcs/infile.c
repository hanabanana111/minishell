/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/03 14:57:54 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirect1(infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		error_exit(infile);
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
