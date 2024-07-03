/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:15:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 15:12:42 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info *info_lstnew(char *cmd)
{
    t_info *p;
    p = (t_info *)ft_calloc(sizeof(t_info));
    if(!p)
        return(NULL);
    p->str = cmd;
    // p->type = 0;
    // p->next = NULL;
}

t_info *info_lstlast(t_info *lst)
{
    if(!lst)
        return(NULL);
    while(lst->next)
        lst = lst->next;
    return(lst);
}

void info_lstadd_back(t_info **lst, t_info *new)
{
    if(!lst)
        return;
    if(!*lst)
    {
        *lst = new;
        return;
    }
    info_lstlast(*lst)->next = new;
}

void	info_lstadd_front(t_info **lst, t_info *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

