/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:33:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 15:42:49 by hakobori         ###   ########.fr       */
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
