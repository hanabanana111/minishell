/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_info_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:13:28 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 20:59:09 by hakobori         ###   ########.fr       */
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

void check_cmd_env_quote(t_info *node, t_status *status)
{
    char q_chr;
    int is_doll;
    int i;
    int count;
    int len;
    // char *pre;
    // char *add;

    is_doll = 0;
    q_chr = '\0';
    i = 0;
    count = 0;
    len = ft_strlen(node->str);
    while(node->str[i])
    {
        if(node->str[i] == '$' && q_chr != '\'')
        {
            if(node->str[i+1] != '\0'|| node->str[i+1] != q_chr || node->str[i+1] != ' ')
            {
                i++;
                printf("s = %s\n",treat_doll(&node->str[i],status));
            }
        }
        if(ft_strchr("\'\"",(node->str[i])))
            q_chr = node->str[i];
        i++;
    }
    // if(is_doll && q_chr != '\'')
    // {
    //     if(node->str[i+1] == q_chr || node->str[i+1] == ' ')
    //         return;
    //     i++;
    //     printf("&node->str[i] = %s\n",&node->str[i]);
    //     printf("s = %s\n",treat_doll(&node->str[i],status));
    // }
}

void check_env(t_info *ret,t_status *status)
{
    t_info *node;

    node = ret;
    while(node)
    {
        check_cmd_env_quote(node,status);
        node = node->next;
    }
}

t_info *treat_info_lst(char **arr,t_status *status)
{
    t_info *ret;

    ret = NULL;
    set_arr_to_lst(arr,&ret);
    check_env(ret, status);
    return(ret);
}