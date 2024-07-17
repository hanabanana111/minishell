/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_emv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:09:17 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/17 16:25:30 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env_l(char **pre_env)
{
	size_t	count;

	count = 0;
	while(pre_env[count])
		count++;
	return (count);
}

void	set_pre_to_current(char **pre_env, char **result)
{
	size_t i;

	i = 0;
	if (!pre_env)
		return;
	while(pre_env[i])
		result[i] = pre_env[i++];
}
 
char	**add_env(t_status *status, )
{
	char	**pre_env;
	char	**result;
	size_t	env_l;

	pre_env = status->envm;
	
	env_l = count_env_l(pre_env);
	result = (char **)ft_calloc(env_l + 2, sizeof(char *));
	if(!result)
		return(NULL);
	set_pre_to_current(pre_env, result);
	
}