/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/27 20:44:40 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (infile_redirect3(infile));
	else
		return (infile_redirect1());
}
