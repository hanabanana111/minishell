/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:10:54 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/04 13:34:56 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfile_redirect1(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	if (fd < 0)
		error_exit(outfile);
	return (fd);
}

int	outfile_redirect2(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (fd < 0)
		error_exit(outfile);
	return (fd);
}

int	determine_outfile(char *cmd, char *next)
{
	if (ft_strncmp(cmd, ">>\0", 3) == 0)
		return (outfile_redirect2(next));
	else if (ft_strncmp(cmd, ">\0", 2) == 0)
		return (outfile_redirect1(next));
}

t_info	*outfile_fd(t_cmd *cmd_lst, t_info *lst)
{
	cmd_lst -> pipe_1 = determine_out(lst -> str, lst -> next -> str);
	if (cmd_lst -> pipe_1 < 0)
	{
		while (lst -> next -> type != PIPE && lst -> next)
			lst = lst -> next;
	}
	return (lst);
}
