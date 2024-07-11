/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:16:48 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/11 15:17:23 by hakobori         ###   ########.fr       */
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
	if (!ft_strncmp(str, "<\0", 2) || !ft_strncmp(str, "<<\0", 3)
		|| !ft_strncmp(str, "<<<\0", 4))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], "<\0", 2))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], "<<\0", 3))
		return (TRUE);
	else if (i && !ft_strncmp(&str[i], "<<<\0", 4))
		return (TRUE);
	else
		return (FALSE);
}

void	set_token_types(t_info *cmd_info)
{
	t_info	*node;

	node = cmd_info;
	while (node)
	{
		if (!node->is_quote && !ft_strncmp(node->str, "|\0", 2))
			node->type = PIPE;
		else if (!node->is_quote && is_redirect_right(node->str))
			node->type = RIGHT;
		else if (!node->is_quote && is_redirect_left(node->str))
			node->type = LEFT;
		else if (node->pre && node->pre->type == RIGHT)//!node->is_quote && 
			node->type = OUT;
		else if (node->pre && node->pre->type == LEFT)//!node->is_quote &&
			node->type = IN;
		else if (node->type == 0)
		{
			if (node == cmd_info || (node->pre && node->pre->type == PIPE))
				node->type = CMD;
			else
				node->type = OPT;
		}
		node = node->next;
	}
}

t_info	*lexer(char *line, t_status *status)
{
	char	**arr;
	t_info	*cmd_info;

	arr = split_to_token(line, " \t\n");
	if (!arr)
		return (NULL);
	cmd_info = NULL;
	set_arr_to_lst(arr, &cmd_info);
	ft_free_2d_array(arr);
	check_env(cmd_info, status);
	format_quote(&cmd_info);
	separator(cmd_info);
	set_token_types(cmd_info);
	return (cmd_info);
}
