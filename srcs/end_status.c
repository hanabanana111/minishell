/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:41:07 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 20:25:24 by rkawahar         ###   ########.fr       */
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
