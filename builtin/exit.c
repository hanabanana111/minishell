/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 22:25:01 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_end_status(t_cmd *lst)
{
	t_cmd *node;
	size_t i;

	i = 0;
	node = lst->next;
	while(node->arg)
	{
		if(!ft_isdigit(node->arg[i++]))
			return (FALSE);
	}
	return (TRUE);
}

int exit_func(t_cmd *lst)
{
	int end_status;
	t_cmd *node;

	end_status = 0;
	if (!lst)
		return(FALSE);
	if (is_end_status(lst))
	{
		node = lst->next;
		end_status = (unsigned char)ft_atoi(node->arg);
	}
	end_status_func(end_status);
	exit(end_status);
	return(TRUE);
}
