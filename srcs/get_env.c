/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:58 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 17:07:26 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **treat_env(char **env)
{
    char **ret;
    size_t i;

    if(!env)
        return(NULL);
    i = 0;
    while(env[i])
        i++;
    ret =(char **)ft_calloc(i+1,sizeof(char *));
    if(!ret)
        return(NULL);
    i = 0;
    while(env[i])
    {
        ret[i] = ft_strdup(env[i]);
        i++;
    }
    return(ret);
}
