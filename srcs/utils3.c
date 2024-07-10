/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:01:32 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 23:01:47 by hakobori         ###   ########.fr       */
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