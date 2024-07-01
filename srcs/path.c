/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:41:23 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/01 16:50:57 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_sl(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            return (1);
    }
    return (0);
}

char    *path_finder(char *cmd, char **env)
{
    char ans;

    if (check_sl(cmd))
        file_finder(cmd);
}