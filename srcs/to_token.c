/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:54:55 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 15:01:27 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s, char *sep)
{
	int		count;
	size_t	i;
	size_t	start;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(sep,s[i]))
			i++;
		start = i;
		while (s[i] && !ft_strchr(sep,s[i]))
			i++;
		if (i > start)
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

	if (!s)
		return (NULL);
	result = (char **)ft_calloc(count_words(s, sep) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	head = result;
	while (*s)
	{
		while (*s && ft_strchr(sep,*s))
			s++;
		start = s;
		while (*s && !ft_strchr(sep,*s))
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
