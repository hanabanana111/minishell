/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:35:05 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/19 17:19:59 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_home(t_status *status)
{
	char	*home_tmp;

	home_tmp = get_value(status->envm, "HOME");
	if (!home_tmp || home_tmp[0] == '\0')
		return (FALSE);
	status->home = home_tmp;
	return (TRUE);
}
