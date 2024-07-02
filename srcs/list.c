/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:13:50 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/02 10:35:08 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *create_nord(void)
{
    t_cmd   *ans;

    ans = (t_cmd *)malloc(sizeof(t_cmd));
    if (ans == NULL)
        error_exit("create_nord");
    ans -> cmd = NULL;
    ans -> path = NULL;
    ans -> arg = (char **)malloc(sizeof(char *));
    ans -> arg[0] = NULL;
    ans -> pipe_0 = NULL;
    ans -> pipe_1 = NULL;
    ans -> next = NULL;
    return (ans);
}

char    **set_args(char *str, char **args)
{
    int     i;
    char    **ans;

    i = 0;
    while(args[i])
        i++;
    ans = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (args[i])
    {
        ans[i] = ft_strdup(args[i]);
        i++;
    }
    ans[i] = ft_strdup(str);
    ans[i + 1] = NULL;
    return (ans);
}

t_cmd   *create_lst(t_info *lst)
{
    t_cmd   *ans;
    t_cmd   *tmp;
    int     i;

    i = 0;
    ans = create_nord();
    i = count_pipe(lst);
    while (i > 0)
    {
        tmp = create_nord();
        connect_lst(ans, tmp);
        i--;
    }
}