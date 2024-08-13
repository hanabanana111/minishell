/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:53:44 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/13 09:09:24 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
	}
	ft_printf(2, "minishell: env: No such file or directory\n");
	end_status_func(127);
	return (0);
}

int	env_func(t_status *status, t_cmd *lst)
{
	size_t	i;

	i = 0;
	if (check_env_path(status->envm) == 0)
		return (1);
	if (lst->pre || lst->next)
		return (0);
	if (!status->envm || !status->envm[i])
	{
		printf("\n");
		return (0);
	}
	while (status->envm[i])
		printf("%s\n", status->envm[i++]);
	return (1);
}
