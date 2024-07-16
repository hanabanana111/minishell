/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:31 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/16 15:15:04 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t count_pipe(t_info *lst)
// {
// 	t_info *node;
// 	size_t count;

// 	count = 0;
// 	node = lst;
// 	while(node)
// 	{
// 		if(!ft_strncmp(node->str,"|\0",2))
// 			count++;
// 		node = node->next;
// 	}
// 	return(count);
// }

int	check_option_n(t_info *lst)
{
	char	*opt;
	size_t	i;

	i = 0;
	if (!lst->str)
		return (FALSE);
	opt = lst->str;
	if (opt[0] == '-')
		i++;
	else
		return (FALSE);
	if (lst->is_quote)
		return (FALSE);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_info	*find_echo_part(t_info *lst)
{
	t_info	*node;

	node = lst;
	while (node && check_option_n(node))
		node = node->next;
	return (node);
}

void	echo_func(t_info *lst)
{
	t_info	*echo_part;
	size_t p_count;
	
	pirntf("pass\n");
	p_count = count_pipe(lst);
	echo_part = find_echo_part(lst);
	if (!echo_part)
		return ;
	while (echo_part)
	{
		if (echo_part->str)
			printf("%s", echo_part->str);
		echo_part = echo_part->next;
	}
}
