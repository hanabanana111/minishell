/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:46:43 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/06 09:40:57 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
