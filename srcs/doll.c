/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:09:34 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 21:24:36 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_env(t_env_quote_info *e_q_info, t_status *status)
{
	size_t	i;
	size_t	n_len;
	size_t	env_len;

	i = 0;
	n_len = ft_strlen(e_q_info->key);
	if (ft_strchr(e_q_info->key, '?'))
		return ;
	while (status->envm[i])
	{
		if (!ft_strncmp(e_q_info->key, status->envm[i], n_len)
			&& status->envm[i][n_len] == '=')
		{
			env_len = ft_strlen(status->envm[i]) - n_len;
			e_q_info->value = (char *)ft_calloc(env_len, sizeof(char));
			if (!e_q_info->value)
				return ;
			ft_strlcpy(e_q_info->value, &status->envm[i][n_len + 1], env_len);
			return ;
		}
		i++;
	}
	e_q_info->value = NULL;
}

void	treat_doll(char const *str, t_env_quote_info *e_q_info)
{
	size_t	count;

	count = 0;
	if (str[0] == '?')
	{
		e_q_info->key = "?";
		e_q_info->value = ft_itoa(end_status_func(-1));
	}
	while (str[count] && !ft_strchr("\'\" ", str[count]))
		count++;
	e_q_info->key = (char *)ft_calloc(count + 1, sizeof(char));
	if (!e_q_info->key)
	{
		e_q_info->key = NULL;
		return ;
	}
	ft_strlcpy(e_q_info->key, str, count + 1);
}

size_t	s_strlen(char *str)
{
	if (!str)
		return (0);
	return (ft_strlen(str));
}

void	free_pre_e_q_info(char **pre, t_env_quote_info *e_q_info)
{
	char	*pre_tmp;
	char	*key_tmp;
	char	*value_tmp;

	pre_tmp = *pre;
	key_tmp = e_q_info->key;
	value_tmp = e_q_info->value;
	e_q_info->key = NULL;
	e_q_info->value = NULL;
	*pre = NULL;
	free(pre_tmp);
	free(key_tmp);
	free(value_tmp);
}

void	ft_chenge_env_to_value(t_info *node, t_env_quote_info *e_q_info)
{
	char	*pre;
	char	*key_tmp;
	char	*value_tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	pre = node->str;
	key_tmp = e_q_info->key;
	value_tmp = e_q_info->value;
	node->len = s_strlen(node->str) - s_strlen(key_tmp) + s_strlen(value_tmp);
	node->str = (char *)ft_calloc(node->len, sizeof(char));
	if (!node->str)
		return (free(pre));
	while (pre[i] != '$')
		node->str[j++] = pre[i++];
	while (value_tmp && *value_tmp)
		node->str[j++] = *value_tmp++;
	while (*key_tmp && pre[++i] == *key_tmp)
		key_tmp++;
	while (pre[++i])
		node->str[j++] = pre[i];
	free_pre_e_q_info(&pre, e_q_info);
}
