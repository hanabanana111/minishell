/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 15:04:02 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void show_syntax_error(char *str)
{
    printf("Command '%s' not found",str);
}



void treat_parser(char *str,int *is_paesed)
{
    char **arr;
    
    arr = token_split(str," \t\n");
    (void)is_paesed;
    // int i;
    // i = 0;
    // while(arr[i])
    //     printf("%s\n",arr[i++]);
    // printf("a\n");
}
