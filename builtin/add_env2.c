/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:31:20 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/22 18:54:23 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_join(char *key)
{
	size_t	key_len;

	key_len = s_strlen(key);
	if (key[key_len - 1] == '+')
	{
		key[key_len - 1] = '\0';
		return (TRUE);
	}
	return (FALSE);
}

int	find_i_of_key(char *key, char **env)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = s_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	change_key_value(t_status *status, char *key, char *new, int is_plus)
{
	int		key_i;
	char	*pre_str;
	char	*new_value;

	key_i = find_i_of_key(key, status->envm);
	pre_str = status->envm[key_i];
	new_value = format_value(new, key);
	if (key_i < 0)
		return (FALSE);
	if (!is_plus)
	{
		pre_str = status->envm[key_i];
		status->envm[key_i] = ft_strjoin(key, "=");
		free(pre_str);
		pre_str = status->envm[key_i];
	}
	status->envm[key_i] = ft_strjoin(pre_str, new_value);
	free(new_value);
	free(pre_str);
	return (TRUE);
}
