/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:55 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 16:47:33 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(const char **str, int *is_second_quote)
{
	int		i;
	char	quote_char;

	i = 0;
	if (ft_strchr("\'\"", **str))
	{
		quote_char = **str;
		i++;
		(*str)++;
		while (**str && **str != quote_char)
		{
			(*str)++;
			i++;
		}
		if (**str == quote_char)
		{
			*is_second_quote = 1;
			return (TRUE);
		}
		else
			return (FALSE);
	}
	*is_second_quote = 1;
	return (TRUE);
}

static int	count_words(char const *s, char *sep)
{
	int			count;
	size_t		i;
	const char	*start;
	const char	*str;
	int			is_second_quote;

	i = 0;
	count = 0;
	str = s;
	while (*str)
	{
		is_second_quote = 0;
		while (*str && ft_strchr(sep, *str))
			str++;
		start = str;
		while (*str && !ft_strchr(sep, *str) && check_quotes(&str,
				&is_second_quote))
		{
			// printf("*str = %c\n",*str);
			str++;
		}
		// printf("*str = %c\n",*str);
		if (!is_second_quote)
			return (-1);
		if (str > start)
			count++;
	}
	return (count);
}

static char	*ft_strndup(char const *s, size_t n)
{
	size_t	i;
	char	*result;

	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}

static void	ft_free_2d_array(char **head)
{
	int	i;

	i = 0;
	while (head[i])
		free(head[i++]);
	free(head);
}

char	**token_split(char const *s, char *sep)
{
	char		**result;
	char		**head;
	const char	*start;
	int			words;
	int			is_second_quote;

	if (!s)
		return (NULL);
	words = count_words(s, sep);
	printf("words = %d\n", words);
	if (words < 0)
		return (NULL);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	head = result;
	while (*s)
	{
		is_second_quote = 0;
		while (*s && ft_strchr(sep, *s))
			s++;
		start = s;
		while (*s && !ft_strchr(sep, *s) && check_quotes(&s, &is_second_quote))
			s++;
		if (s > start)
		{
			*result++ = ft_strndup(start, s - start);
			if (!*(result - 1))
				return (ft_free_2d_array(head), NULL);
		}
	}
	return (head);
}
