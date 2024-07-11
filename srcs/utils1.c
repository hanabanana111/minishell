/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:31:41 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/09 13:20:49 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(char *str)
{
	perror(str);
	exit(1);
}

int	count_pipe(t_info *lst)
{
	int	ans;

	ans = 0;
	while (lst)
	{
		if (lst -> type == PIPE)
			ans++;
		lst = lst -> next;
	}
	return (ans);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
