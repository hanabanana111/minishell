/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/18 01:02:45 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_end_status_digits(t_cmd *lst)
{
	size_t	i;

	i = 0;
	while (lst->arg[1][i])
	{
		if (!ft_isdigit(lst->arg[1][i++]))
			return (FALSE);
	}
	return (TRUE);
}
int	write_error_invalid_argment(char *cmd)
{
	write(2, &"minishell: exit: ", 17);
	write(2, cmd, s_strlen(cmd));
	write(2, &": numeric argument required\n", 28);
	return (2);
}
int	write_error_str(char *str)
{
	write(2, str, s_strlen(str));
	return (2);
}

int	is_pipe(t_cmd *lst)
{
	if (lst->pre || lst->next)
		return (TRUE);
	return (FALSE);
}

int	exit_func(t_cmd *lst, int is_parents)
{
	int		end_status;
	t_cmd	*node;

	end_status = 0;
	node = lst;
	if (!is_pipe(lst) && is_parents)
		printf("exit\n");
	if (!node->arg[1])
		end_status = 0;
	else if (!is_end_status_digits(lst))
		end_status = write_error_invalid_argment(lst->arg[1]);
	else if (node->arg[2])
		end_status = write_error_str("minishell: exit: too many arguments\n");
	else if (is_end_status_digits(lst))
		end_status = (unsigned char)ft_atoi(node->arg[1]);	
	if (is_parents && !is_pipe(lst))
		exit(end_status);
	dprintf(2,"exit func : end_status = [%d]\n",end_status);
	if (!is_parents)
		exit(end_status);
	return (0);
}
