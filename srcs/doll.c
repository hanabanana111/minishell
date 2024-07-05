/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:09:34 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 21:04:20 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_env(char *name,t_status *status)
{
    size_t i;
    size_t n_len;
    size_t env_len;
    char *ret;
    

    i = 0;
    n_len = ft_strlen(name);
    while(status->envm[i])
    {
        if(ft_strncmp(name,status->envm[i],n_len) && status->envm[n_len] == '=')
        {
            env_len = ft_strlen(status->envm[i]) - n_len;
            ret = (char *)ft_calloc(env_len,sizeof(char));
            ft_strlcpy(ret,status->envm[i][len],count+1);
        }
        i++;
    }
    return(NULL);
}

char *treat_doll(char const *str,t_status *status)
{
    char *ret;
    size_t count;
    
    count = 0;
    if(str[0] == '?')
        return(ft_itoa(status->end_status));
    while(str[count] && !ft_strchr("\'\" ",str[count]))
        count++;
    printf("count = %zu\n",count);
    ret =(char *)ft_calloc(count+1,sizeof(char));
    ft_strlcpy(ret,str,count+1);
    
    return(ret);
}
