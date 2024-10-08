/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:15:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 19:19:47 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*info_lstnew(char *cmd)
{
	t_info	*p;

	p = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!p)
		return (NULL);
	p->str = ft_strdup(cmd);
	p->pre = NULL;
	p -> type = -1;
	p -> e_flg = 0;
	p -> flg = 0;
	return (p);
}

t_info	*info_lstlast(t_info *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	info_lstadd_back(t_info **lst, t_info *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
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
