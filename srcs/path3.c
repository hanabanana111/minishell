/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:28:05 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/23 16:30:43 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_paths(int i, char **paths)
{
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths[i]);
	free(paths);
}
