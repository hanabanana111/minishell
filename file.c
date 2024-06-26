/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:26:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/06/26 18:39:44 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	determine_infile(t_info *lst)
{
	int	ans;

	while (lst)
	{
		if (lst -> type == 4)
		{
			if (ft_strncmp(lst -> str, "<<\0", 3) == 0)
				ans = open
		}
		lst = lst -> next;
	}
}
