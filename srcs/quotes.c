/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:06:47 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/04 21:55:08 by hakobori         ###   ########.fr       */
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

void	treat_first_quote(char *q_chr, char const *s, size_t *i, int *q_count)
{
	*q_chr = s[*i];
	(*q_count)++;
	(*i)++;
}

void	treat_second_quote(char *q_chr, size_t *i, int *q_count)
{
	(*q_count)++;
	if (*q_count == 2)
	{
		*q_chr = 0;
		*q_count = 0;
	}
	(*i)++;
}

char	*format_quotes_and_strndup(char const *s, size_t n,int end_status)
{
	size_t	i;
	size_t	j;
	char	*result;
	char	q_chr;
	int		q_count;

	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	q_chr = 0;
	q_count = 0;
	while (s[i] && i < n)
	{
		if (!q_chr && ft_strchr("\'\"", s[i]))
			treat_first_quote(&q_chr, s, &i, &q_count);
		else if (q_chr && s[i] == q_chr)
			treat_second_quote(&q_chr, &i, &q_count);
		else
			result[j++] = s[i++];
		// if(q_chr != '\'' && s[i] == '$')
		// {
		// 	treat_doll(&s[i+1],&end_status);
		// }
	}
	(void)end_status;
	return (result);
}
