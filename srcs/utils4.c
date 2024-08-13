/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:04:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/13 22:09:22 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace_isdigit_str(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (FALSE);
	while(str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if(!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
