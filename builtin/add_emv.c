/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_emv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:09:17 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 17:59:31 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env_l(char **pre_env)
{
	size_t	count;

	count = 0;
	while (pre_env[count])
		count++;
	return (count);
}

char	**set_pre_to_current(char **pre_env, size_t env_l)
{
	size_t	i;
	char	**result;

	i = 0;
	result = (char **)ft_calloc(env_l + 2, sizeof(char *));
	if (!result)
		return (NULL);
	while (pre_env[i])
		result[i] = pre_env[i++];
	return (result);
}

int	add_new_key(t_status *status, char **pre_env, char *new)
{
	size_t	env_l;

	env_l = count_env_l(pre_env);
	status->envm = set_pre_to_current(pre_env, env_l);
	free(pre_env);
	status->envm[env_l] = new;
	return (TRUE);
}

int	add_env(t_status *status, char *new)
{
	char	**pre_env;
	char	*key;
	int	is_plus;
	int is_key_i;

	pre_env = status->envm;
	key = key_format(new);
	is_plus = is_join(key);
	is_key_i = find_i_of_key(key, status->envm);
	if (!key)
		return (add_new_key(status, pre_env, new));
	else
		return (change_key_value(status, key, new));
}
