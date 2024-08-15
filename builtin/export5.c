/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:14:44 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/15 16:15:32 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_func2(char **arg, t_status *status, t_cmd *first)
{
	(void)first;
	if (ft_len(arg) == 1)
		print_export(status->exp);
	return (1);
}
