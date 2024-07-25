/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:16:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/25 14:37:51 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	treat_first_quote(char *q_chr, char const *s, size_t *i,
		t_info *node)
{
	if (s[*i] == '\'')
		node->is_quote = SINGLE;
	else if (s[*i] == '\"')
		node->is_quote = DOUBLE;
	*q_chr = s[*i];
	(*i)++;
}

static void	treat_second_quote(char *q_chr, size_t *i)
{
	*q_chr = 0;
	(*i)++;
}

char	*delete_quotes_and_strndup(char *src, size_t n, t_info *node)
{
	size_t	i;
	size_t	j;
	char	*result;
	char	q_chr;

	i = 0;
	j = 0;
	q_chr = 0;
	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (src[i] && i < n)
	{
		if (!q_chr && ft_strchr("\'\"", src[i]))
			treat_first_quote(&q_chr, src, &i, node);
		else if (q_chr && src[i] == q_chr)
			treat_second_quote(&q_chr, &i);
		else
			result[j++] = src[i++];
	}
	return (result);
}

void	format_quote(t_info **cmd_lst)
{
	t_info	*node;
	char	*pre;

	node = *cmd_lst;
	while (node)
	{
		pre = node->str;
		node->str = delete_quotes_and_strndup(node->str, ft_strlen(node->str),
				node);
		node = node->next;
		free(pre);
	}
}
