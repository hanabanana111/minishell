/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:13:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/04 19:20:43 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_arr_to_lst(char **arr,t_info **ret)
{
    int i;
    t_info *node;

    i = 0;
    while(arr[i])
    {
        if(!*ret)
        {
            *ret = info_lstnew(arr[i]);
            node = *ret;
        }
        else
        {
            node->next = info_lstnew(arr[i]);
            node = node->next;
        }
        i++;
    }
}

t_info *treat_info_lst(char **arr)
{
    t_info *ret;

    ret = NULL;
    set_arr_to_lst(arr,&ret);
    return(ret);
}