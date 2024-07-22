/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:31:40 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/22 19:44:25 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_func(t_status *status, t_cmd *first)
{
	int	i;

	if (ft_lstlen(first) > 1)
		return (0);
	i = 1;
	while (first -> arg[i])
	{
		status -> exp = remove_exp(status -> exp, first -> arg[i]);
		status -> envm = remove_env(status -> envm, first -> arg[i]);
		i++;
	}
	return (1);
}
