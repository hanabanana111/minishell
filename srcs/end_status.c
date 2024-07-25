/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:41:07 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/25 14:43:15 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_status_func(int status)
{
	static int	end_status;

	if (status >= 0)
		end_status = status;
	else
		return (end_status);
	return (0);
}

char	*set_get_readline(char *new)
{
	static char	*line;

	if (new)
		line = new;
	return (line);
}
