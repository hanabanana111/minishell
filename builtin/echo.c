/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:51:31 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/16 16:09:12 by kawaharadar      ###   ########.fr       */
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

int	check_option_n(char *str)
{
	char	*opt;
	size_t	i;

	i = 0;
	if (!str)
		return (FALSE);
	opt = str;
	if (opt[0] == '-')
		i++;
	else
		return (FALSE);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	find_echo_part(char **arg)
{
	int	i;

	i = 1;
	while (arg[i] && check_option_n(arg[i]))
		i++;
	return (i);
}

int	echo_func(t_cmd *lst)
{
	int	echo_part;
	
	printf("builtin\n");
	echo_part = find_echo_part(lst -> arg);
	if (!echo_part)
		return (1);
	if (echo_part > 1)
	{
		while (lst -> arg[echo_part])
		{
			printf("%s", lst -> arg[echo_part]);
			if(!lst -> arg[echo_part + 1])
				return (1);
			else
				printf(" ");
			echo_part++;
		}
	}
	else
	{
		while (lst -> arg[echo_part])
		{
			printf("%s", lst -> arg[echo_part]);
			if(!lst -> arg[echo_part + 1])
				printf("\n");
			else
				printf(" ");
			echo_part++;
		}
	}
	return (1);
}
