/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:09:13 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/26 17:39:39 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_execve(int num)
{
	static int	is_exe_flg;

	if (num >= 0)
		is_exe_flg = num;
	return (is_exe_flg);
}

// int is_minishell(char *path)
// {
// 	size_t len;
// 	size_t i;
// 	char *tmp;

// 	len = ft_strlen(path);
// 	if (len < 10)
// 		return (FALSE);
// 	tmp = ft_strdup("minishell");
// 	i = 9;
// 	while(i >= 0 && len >= 0)
// 	{
// 		if(tmp[i] != path[--len])
// 		i--;
// 	}
// }