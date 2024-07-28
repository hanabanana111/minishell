/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/28 20:49:47 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_end_status_digits(t_cmd *lst)
{
	size_t	i;

	i = 0;
	if (lst->arg[1][i] == '-' || lst->arg[1][i] == '+')
		i++;
	while (lst->arg[1][i])
	{
		if (ft_isdigit(lst->arg[1][i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	write_error_invalid_argment(char *cmd, t_status *status)
{
	char	*pronpt;

	pronpt = pronpt_ps1(status->envm);
	write(2, pronpt, s_strlen(pronpt));
	write(2, &": exit: ", 8);
	write(2, cmd, s_strlen(cmd));
	write(2, &": numeric argument required\n", 28);
	return (2);
}

int	write_error_str(char *str)
{
	char	*pronpt;

	pronpt = pronpt_ps1(NULL);
	write(2, pronpt, s_strlen(pronpt));
	write(2, str, s_strlen(str));
	return (2);
}

int	is_pipe(t_cmd *lst)
{
	if (lst->pre || lst->next)
		return (TRUE);
	return (FALSE);
}

int	exit_func(t_cmd *lst, int is_parents, t_status *status)
{
	int		end_status;
	t_cmd	*node;

	end_status = 0;
	node = lst;
	if (!is_pipe(lst) && is_parents)
		printf("exit\n");
	if (!node->arg[1])
		end_status = 0;
	else if (is_end_status_digits(lst) == FALSE)
		end_status = write_error_invalid_argment(lst->arg[1], status);
	else if (node->arg[2])
		end_status = write_error_str(": exit: too many arguments\n");
	else if (is_end_status_digits(lst))
		end_status = (unsigned char)ft_atoi(node->arg[1]);
	if (is_parents && !is_pipe(lst))
		exit(end_status);
	if (!is_parents)
		exit(end_status);
	return (0);
}
