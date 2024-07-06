/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/06 20:05:48 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void show_syntax_error(char *str)
{
    printf("Command '%s' not found",str);
}

void treat_parser(char *line,t_status *status)
{
    char **arr;
    t_info *cmd_info;
    status->end_status = 0;
    arr = split_to_token(line," \t\n");
    if(!arr)
        return;
    cmd_info = treat_info_lst(arr,status);
    ft_free_2d_array(arr);
    status->end_status = to_parse_lst(&cmd_info);
    t_info *node;
    node = cmd_info;
    while(node)
    {
        printf("cmd = %s\n",node->str);
        node=node->next;
    }
}
