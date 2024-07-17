/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:53:44 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 21:57:38 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_func(char **env)
{
	size_t i;

	i = 0;
	if(!env || !env[i])
	{
		printf("\n");
		return(0);
	}
	while(env[i])
		printf("%s\n",env[i++]);
	return(1);
}
