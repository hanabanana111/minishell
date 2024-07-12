/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:27:42 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/12 18:52:00 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_lst_details(t_info	*cmd_info, char **envm)
{
	check_env(cmd_info, envm);
	format_quote(&cmd_info);
	separator(cmd_info);
	set_token_types(&cmd_info);
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
	set_lst_details(cmd_info, status->envm);
	return (cmd_info);
}
