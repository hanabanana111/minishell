/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prosses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:54:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/02 13:06:27 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_miniprocess(t_info *lst, char **env)
{
	int		infile_fd;
	int		outfile_fd;
	t_cmd	*info;

	info = create_lst(lst);
	infile_fd = 0;
	outfile_fd = 1;
	while (lst -> type != PIPE && lst)
	{
		if (lst -> type == IN)
			infile_fd = determine_infile(lst -> str, lst -> next -> str, infile_fd);
		else if (lst -> type == OUT)
			outfile_fd = determine_outfile(lst -> str, lst -> next -> str, outfile_fd);
		else if (lst -> type == CMD)
		{
			info -> cmd = lst -> str;
			info -> arg = set_args(lst -> str, info -> arg);
		}
		else if (lst -> type == OPT)
			info -> arg = set_args(lst -> str, info -> arg);
		lst = lst -> next;
	}
	info -> path = path_finder(info -> cmd, env);
}