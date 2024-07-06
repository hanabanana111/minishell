/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:06:47 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/06 20:50:33 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(const char **str)
{
	int	q_chr;

	if (ft_strchr("\'\"", **str))
	{
		q_chr = (int)**str;
		(*str)++;
		while (**str && **str != q_chr)
			(*str)++;
		if (**str == q_chr)
			return (q_chr);
		else
			return (0);
	}
	return (-1);
}

char	*consider_quotes_and_strndup(char const *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*result;
	char	q_chr;

	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	q_chr = 0;
	while (s[i] && i < n)
	{
		if (!q_chr && ft_strchr("\'\"", s[i]))
			q_chr = s[i];
		else if (q_chr && s[i] == q_chr)
			q_chr = 0;
		result[j++] = s[i++];
	}
	return (result);
}
