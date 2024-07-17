/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:57:30 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 19:20:47 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim2(char *str, int index)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(str) - index + 1);
	if (ans == NULL)
		error_exit("ft_strtrim2");
	i = 0;
	while (str[index])
		ans[i++] = str[index++];
	ans[i] = '\0';
	free(str);
	return (ans);
}
