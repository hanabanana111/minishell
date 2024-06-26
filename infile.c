/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/26 20:03:18 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_redirect2(char *eof)
{
	int		file_pipe[2];
	int		error_flg;
	char	*str;

	str = redirect_gnl(eof);
}

int	infile_redirect3(char *str)
{
	int		file_pipe[2];
	size_t	len;
	int		error_flg;

	pipe(file_pipe);
	len = ft_strlen(str);
	error_flg = write(file_pipe[1], str, len);
	if (error_flg < 0)
		error_exit("infile_redirect");
	close(file_pipe[1]);
	return (file_pipe[0]);
}

int	determine_infile(t_info *lst)
{
	char	*redirect;
	char	*after_re;

	while (lst)
	{
		if (lst -> type == 4)
		{
			redirect = lst -> str;
			after_re = lst -> next -> str;
		}
		lst = lst -> next;
	}
	if (ft_strncmp(redirect, "<<<\0", 4) == 0)
		return (infile_redirect3(after_re));
	else if (ft_strncmp(redirect, "<<\0", 3) == 0)
		return (infile_redirect2(after_re));
	else
		return (infile_redirect1(after_re));
}
