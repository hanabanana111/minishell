/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/27 21:11:34 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirect2(char *str)
{
	int	file_pipe[2];

	if (pipe(file_pipe) < 0)
		
}

int	determine_infile(t_info *lst)
{
	char	*redirect;
	char	*infile;

	while (lst)
	{
		if (lst -> type == 4)
		{
			redirect = lst -> str;
			infile = lst -> next -> str;
		}
		lst = lst -> next;
	}
	if (ft_strncmp(redirect, "<<\0", 3) == 0)
		return (infile_redirect2(infile));
	else
		return (infile_redirect1(infile));
}
