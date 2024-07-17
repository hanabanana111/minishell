/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 22:53:22 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_end_status_digits(t_cmd *lst)
{
	t_cmd *node;
	size_t i;

	i = 0;
	node = lst->next;
	while(node->arg)
	{
		if(!ft_isdigit(node->arg[1][i++]))
			return (FALSE);
	}
	return (TRUE);
}

int exit_func(t_cmd *lst)
{
	int end_status;
	t_cmd *node;

	end_status = 0;
	node = lst;
	printf("exit\n");
	if (!node->arg[1])
		end_status = 0;
	else if(!is_end_status_digits(lst))
	{
		printf("minishell: exit: %s: numeric argument required\n", node->arg[1]);
		end_status = 2;
	}
	else if (node->arg[2])
	{
		printf("minishell: exit: too many arguments\n");
		end_status = 2;
	}
	else if (is_end_status_digits(lst))
		end_status = (unsigned char)ft_atoi(node->arg[1]);
	end_status_func(end_status);
	exit(end_status);
	return(TRUE);
}
