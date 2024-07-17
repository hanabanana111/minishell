/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:01:32 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 21:43:41 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char const *s, size_t n)
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

int	ft_lstlen(t_cmd *first)
{
	t_cmd	*lst;
	int		ans;

	ans = 0;
	lst = first;
	while (lst)
	{
		ans++;
		lst = lst -> next;
	}
	return (ans);
}
