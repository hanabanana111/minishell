/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:33:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 19:50:42 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(t_cmd *lst, t_status *status)
{
	if (strncmp(lst -> cmd, "/bin/echo\0", 10) == 0)
		return (echo_func(lst));
	else if (strncmp(lst -> cmd, "echo\0", 5) == 0)
		return (echo_func(lst));
	if (strncmp(lst -> cmd, "/bin/pwd\0", 9) == 0)
		return (pwd_func(status->envm));
	else if (strncmp(lst -> cmd, "pwd\0", 4) == 0)
		return (pwd_func(status->envm));
	return (0);
}

int	builtin2(t_cmd *lst, t_status *status)
{
	if (ft_strncmp(lst -> cmd, "export\0", 7) == 0)
		return (export_func(lst -> arg, status, lst));
	return (0);
}
