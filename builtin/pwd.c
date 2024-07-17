/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:53:24 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 15:22:23 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_func(char **env, t_cmd *lst)
{
	char *value;
	
	value = get_value(env,"PWD");
	if(!value)
		return(FALSE);
	printf("%s\n",value);
	return(TRUE);
}
