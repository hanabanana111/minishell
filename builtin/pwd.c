/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:53:24 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 15:27:53 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_func(char **exp)
{
	char *value;
	
	value = get_value(exp,"PWD");
	if(!value)
		return(FALSE);
	printf("%s\n",value);
	free(value);
	return(TRUE);
}
