/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:20 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/31 13:43:59 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error_str(t_status *status,char *str)
{
	char	*pronpt;

	pronpt = pronpt_ps1(status->envm);
	write(2, pronpt, s_strlen(pronpt));
	write(2, str, s_strlen(str));
	free(pronpt);
	return (2);
}
