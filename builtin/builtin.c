/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:33:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/23 22:00:42 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(t_cmd *lst, t_status *status)
{
	if (ft_strncmp(lst->cmd, "/bin/echo\0", 10) == 0)
		return (echo_func(lst));
	else if (ft_strncmp(lst->cmd, "echo\0", 5) == 0)
		return (echo_func(lst));
	if (ft_strncmp(lst->cmd, "/bin/pwd\0", 9) == 0)
		return (pwd_func(status));
	else if (ft_strncmp(lst->cmd, "pwd\0", 4) == 0)
		return (pwd_func(status));
	if (ft_strncmp(lst->cmd, "export\0", 7) == 0)
		return (export_func2(lst->arg, status, lst));
	if (ft_strncmp(lst->cmd, "exit\0", 5) == 0)
		return (exit_func(lst, 0));
	if (ft_strncmp(lst->cmd, "env\0", 4) == 0)
		return (env_func(status->envm, lst));
	if (ft_strncmp(lst->cmd, "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(lst->cmd, "unset\0", 6) == 0)
		return (1);
	return (0);
}

int	builtin2(t_cmd *lst, t_status *status)
{
	if (lst -> cmd == NULL)
		return (0);
	if (ft_strncmp(lst->cmd, "export\0", 7) == 0)
		return (export_func(lst->arg, status, lst));
	if (ft_strncmp(lst->cmd, "exit\0", 5) == 0)
		return (exit_func(lst, 1));
	if (ft_strncmp(lst->cmd, "env\0", 4) == 0)
		return (env_func(status->envm, lst));
	if (ft_strncmp(lst->cmd, "cd\0", 3) == 0)
		return (ft_cd(lst, status));
	if (ft_strncmp(lst->cmd, "unset\0", 6) == 0)
		return (unset_func(status, lst));
	return (0);
}

int	check_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strncmp(cmd, "/bin/echo\0", 10) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "/bin/pwd\0", 9) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit\0", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env\0", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset\0", 6) == 0)
		return (1);
	return (0);
}
