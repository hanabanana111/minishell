/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:10:54 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/12 17:12:07 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	outfile_redirect1(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0000644);
	return (fd);
}

int	outfile_redirect2(char *outfile)
{
	int	fd;

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

t_info	*outfile_fd(t_cmd *cmd_lst, t_info *lst)
{
	char	*e_str;

	if (cmd_lst -> pipe_1 != 1)
		close(cmd_lst -> pipe_1);
	cmd_lst -> pipe_1 = determine_outfile(lst -> str, lst -> next -> str);
	if (cmd_lst -> pipe_1 < 0)
	{
		cmd_lst -> error_file = ft_strjoin(lst -> next -> str, ": ");
		if (cmd_lst -> error_file == NULL)
			error_exit("outfile_fd");
		e_str = strerror(errno);
		cmd_lst -> error_file = ft_strjoin2(cmd_lst -> error_file, e_str);
		if (cmd_lst -> error_file == NULL)
			error_exit("outfile_fd");
		while (lst -> next && lst -> next -> type != PIPE)
			lst = lst -> next;
	}
	return (lst);
}
