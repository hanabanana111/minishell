/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:16:48 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/07 23:59:13 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t is_digits_digits(char *str,size_t i)
{
    size_t j;

    j = i;
    while(str[j] && ft_isdigit(str[j]))
        j++;
    return(j);
}

int is_redirect_right(char *str)
{
    size_t i;
    size_t j;

    i = 0;
    j = is_digits_digits(str,i);
    if(!ft_strncmp(str,">",1) || !ft_strncmp(str,">>",2))
        return(TRUE);
    else if(j && !ft_strncmp(&str[j],">",1))
        return(TRUE);
    else if(j && !ft_strncmp(&str[j],">>",2))
        return(TRUE);
    else
        return(FALSE);
}

int is_redirect_left(char *str)
{
    if(!ft_strncmp(str,"<",2) || !ft_strncmp(str,"<<",2))
        return(TRUE);
    else if(ft_strchr("012",str[0]) && !ft_strncmp(&str[1],"<",1))
        return(TRUE);
    else if(ft_strchr("012",str[0]) && !ft_strncmp(&str[1],"<<",2))
        return(TRUE);
    else
        return(FALSE);
}

void set_token_types(t_info *cmd_info)
{
    t_info *node;
    
	node = cmd_info;
	while (node)
	{
		if(!ft_strncmp(node->str,"|",1))
            node->type = PIPE;
        else if(is_redirect_right(node->str))
            node->type = RIGHT;
        else if(is_redirect_left(node->str))
            node->type = LEFT;
        else if(node->pre && node->pre->type == RIGHT)
            node->type = OUT;
        else if(node->pre && node->pre->type == LEFT)
            node->type = IN;
        else if(node->type == 0)
        {
            if(node == cmd_info ||(node->pre && node->pre->type == PIPE))
            {
                node->type = CMD;
            }
            else
            {
                node->type = OPT;
            }
        }
		node = node->next;
	}
}

t_info *lexer(char *line,t_status *status)
{
    char **arr;
    t_info *cmd_info;
    
    arr = split_to_token(line," \t\n");
    if(!arr)
        return(NULL);
    cmd_info = NULL;
    set_arr_to_lst(arr,&cmd_info);
	check_env(cmd_info, status);
	format_quote(&cmd_info);
    set_token_types(cmd_info);
    ft_free_2d_array(arr);
    return(cmd_info);
}
