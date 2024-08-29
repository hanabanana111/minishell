/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:47:14 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/29 18:56:41 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_heredoc_pre_size(size_t *i, size_t *j, char **pre, t_info *node)
{
	*i = 0;
	*j = 0;
	*pre = node->str;
}

int	is_valid_key(char *pre, size_t i)
{
	if (pre[i] && pre[i + 1])
	{
		if (ft_strchr("_?", pre[i + 1]) || ft_isalpha(pre[i + 1]))
			return (TRUE);
	}
	return (FALSE);
}
