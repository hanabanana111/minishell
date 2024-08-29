/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:37:20 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/29 19:21:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_valid_env(size_t *count, const char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return ;
	if (ft_isdigit(str[i]) || ft_strchr("$", str[i]))
	{
		(*count)++;
		return ;
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && !ft_strchr("_",
				str[i]))
			break ;
		i++;
		(*count)++;
	}
}

int	is_doll(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	while_key_incriment_i(char *key_tmp, char *pre, int *i)
{
	int	k;

	k = 0;
	while (key_tmp[k] && pre[++(*i)] == key_tmp[k])
		k++;
	if (key_tmp && *key_tmp)
		(*i)++;
}

int	init_heredoc_value(t_info *node, t_env_quote_info *e_q_info, char **key_tmp,
		char **value_tmp)
{
	*key_tmp = e_q_info->key;
	*value_tmp = e_q_info->value;
	node->len = s_strlen(node->str) - s_strlen(*key_tmp) + s_strlen(*value_tmp)
		+ 2;
	if (*key_tmp && *key_tmp[0] == '\0')
		node->len += 1;
	node->str = (char *)ft_calloc(node->len, sizeof(char));
	if (!node->str)
		return (1);
	return (0);
}

void	ft_chenge_env_to_value_heredoc(t_info *node, t_env_quote_info *e_q_info,
		size_t node_i)
{
	char	*pre;
	char	*key_tmp;
	char	*value_tmp;
	size_t	i;
	size_t	j;

	init_heredoc_pre_size(&i, &j, &pre, node);
	if (init_heredoc_value(node, e_q_info, &key_tmp, &value_tmp))
		return (free(pre));
	while (i < node_i)
		node->str[j++] = pre[i++];
	if (is_valid_key(pre, i))
	{
		while (value_tmp && *value_tmp)
			node->str[j++] = *value_tmp++;
		while (*key_tmp && pre[++i] == *key_tmp)
			key_tmp++;
		i++;
	}
	if (ft_strncmp("$$", &pre[i], 2) == 0)
		i += 2;
	while (pre[i])
		node->str[j++] = pre[i++];
	free_pre_e_q_info(&pre, e_q_info);
}
