/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:16:48 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/20 16:28:02 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	is_digits_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int	is_redirect_right(char *str)
{
	size_t	i;

	i = is_digits_digits(str);
	if (!ft_strncmp(str, ">\0", 2) || !ft_strncmp(str, ">>\0", 3))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], ">\0", 2))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], ">>\0", 3))
		return (TRUE);
	else
		return (FALSE);
}

int	is_redirect_left(char *str)
{
	size_t	i;

	i = is_digits_digits(str);
	if (!ft_strncmp(str, "<\0", 2) || !ft_strncmp(str, "<<\0", 3))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], "<\0", 2))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], "<<\0", 3))
		return (TRUE);
	else
		return (FALSE);
}

void	cmd_checker(t_info *node)
{
	int	flg;

	flg = 0;
	while (node)
	{
		if (node->type == -1)
		{
			if (flg == 0 && !(ft_strncmp(node->str, "\0", 1) == 0 && node->key))
			{
				node->type = CMD;
				flg = 1;
			}
			else if (flg)
				node->type = OPT;
		}
		else if (node->type == PIPE)
			flg = 0;
		node = node->next;
	}
}

void	set_token_types(t_info **cmd_info)
{
	t_info	*node;

	node = *cmd_info;
	while (node)
	{
		if (!node->is_quote && !ft_strncmp(node->str, "|\0", 2))
			node->type = PIPE;
		else if (!node->is_quote && is_redirect_right(node->str))
			node->type = RIGHT;
		else if (!node->is_quote && is_redirect_left(node->str))
			node->type = LEFT;
		else if (node->pre && node->pre->type == RIGHT)
			node->type = OUT;
		else if (node->pre && node->pre->type == LEFT)
			node->type = IN;
		node = node->next;
	}
	node = *cmd_info;
	cmd_checker(node);
}
