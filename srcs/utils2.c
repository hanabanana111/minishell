/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:46:43 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/12 14:17:12 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ans;
	int		i;
	int		l;

	ans = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	l = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	while (s2[l])
	{
		ans[i] = s2[l];
		i++;
		l++;
	}
	ans[i] = '\0';
	free(s1);
	return (ans);
}

t_info	*decide_file(t_info *first)
{
	t_info	*lst;

	lst = first;
	while (lst)
	{
		if (lst -> type == RIGHT)
			lst -> next -> type = OUT;
		else if (lst -> type == LEFT)
			lst -> next -> type = IN;
		lst = lst -> next;
	}
	return (first);
}
