/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:31:40 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/15 16:08:26 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_exist(char **env, char *str)
{
	int		i;
	char	*env_str;

	i = 0;
	env_str = ft_strjoin(str, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], env_str, ft_strlen(env_str)) == 0)
		{
			free(env_str);
			return (1);
		}
		i++;
	}
	free(env_str);
	return (0);
}

char	**change_shlvl_exp(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		if (ft_strncmp(exp[i], "declare -x SHLVL=", 17) == 0)
		{
			free(exp[i]);
			exp[i] = ft_strdup("declare -x SHLVL=\"0\"");
		}
		i++;
	}
	return (exp);
}

char	**change_shlvl_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup("SHLVL=0");
		}
		i++;
	}
	return (env);
}

int	unset_func(t_status *status, t_cmd *first)
{
	int	i;

	if (ft_lstlen(first) > 1)
		return (0);
	i = 1;
	while (first -> arg[i])
	{
		if (ft_strncmp(first -> arg[i], "SHLVL\0", 6) == 0)
		{
			status -> exp = change_shlvl_exp(status -> exp);
			status -> envm = change_shlvl_env(status -> envm);
		}
		else if (ft_strncmp(first -> arg[i], "_\0", 2))
		{
			status -> exp = remove_exp(status -> exp, first -> arg[i]);
			if (check_env_exist(status -> envm, first -> arg[i]))
				status -> envm = remove_env(status -> envm, first -> arg[i]);
		}
		i++;
	}
	return (1);
}
