/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:55 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 22:07:01 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_word(const char **str, char *sep, const char **start)
{
	int	quote_char;

	while (**str && ft_strchr(sep, **str))
		(*str)++;
	*start = *str;
	while (**str && !ft_strchr(sep, **str))
	{
		quote_char = check_quotes(str);
		if (!quote_char)
			return (FALSE);
		(*str)++;
	}
	return (TRUE);
}

static int	count_words(char const *s, char *sep)
{
	int			count;
	const char	*start;
	const char	*str;

	count = 0;
	str = s;
	if (!s || !sep)
		return (-1);
	while (*str)
	{
		if (!find_word(&str, sep, &start))
		{
			printf("Invalid quotes\n");
			return (-1);
		}
		if (str > start)
			count++;
	}
	return (count);
}

void	ft_free_2d_array(char **head)
{
	int	i;

	i = 0;
	while (head[i])
		free(head[i++]);
	free(head);
}

char	**split_to_token(char const *s, char *sep)
{
	char		**result;
	char		**head;
	const char	*start;
	int			words;

	words = count_words(s, sep);
	if (!s || words < 0)
		return (NULL);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	head = result;
	while (*s)
	{
		find_word(&s, sep, &start);
		if (s > start)
		{
			*result++ = consider_quotes_and_strndup(start, s - start);
			if (!*(result - 1))
				return (ft_free_2d_array(head), NULL);
		}
	}
	return (head);
}
