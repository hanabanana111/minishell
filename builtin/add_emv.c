/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_emv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:09:17 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/04 23:56:37 by hakobori         ###   ########.fr       */
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
	{
		result[i] = pre_env[i];
		i++;
	}
	return (result);
}

int	add_new_key(t_status *status, char **pre_env, char *new, int is_join)
{
	size_t	env_l;
	size_t	i;
	size_t	move_size;

	env_l = count_env_l(pre_env);
	status->envm = set_pre_to_current(pre_env, env_l);
	free(pre_env);
	if (is_join)
	{
		i = 0;
		while (new[i] != '=')
			i++;
		move_size = s_strlen(new) - i + 1;
		ft_memmove(&new[i - 1], &new[i], move_size);
	}
	status->envm[env_l] = ft_strdup(new);
	return (TRUE);
}

int	add_env(t_status *status, char *new)
{
	char	**pre_env;
	char	*key;
	int		is_key_i;
	int		is_join_num;
	int		ret;

	pre_env = status->envm;
	is_join_num = is_join(new);
	key = key_format(new);
	is_key_i = find_i_of_key(key, status->envm);
	if (is_key_i == -1)
		ret = add_new_key(status, pre_env, new, is_join_num);
	else
		ret = change_key_value(status, key, new, is_join_num);
	free(key);
	return (ret);
}
