/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:09:34 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 17:57:04 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *treat_doll(char const *str,t_status *status,size_t *i,char *result)
{
    char *ret;
    char *end_status_str;
    
    ret = NULL;
    end_status_str = ft_itoa(status->end_status);
    if(ft_strncmp("$?",str,2))
        ret = end_status_str;
    // else if(*str == '$' && *(str+1) == '\0')
    // {
    // }
    printf("end_status_str = %s\n",end_status_str);
    printf("str = %s\n",str);
    (void)i;
    (void)result;
    return(ret);
}
