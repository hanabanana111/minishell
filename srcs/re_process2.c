/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_process2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:10:14 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/15 17:13:41 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_process2(char *str, t_cmd *lst, t_status *env_lst, int fd)
{
	int		i;
	t_info	*tmp;

	i = 1;
	while (str != NULL)
	{
		tmp = create_info(str, lst->cmd, i++);
		set_lst_details(&tmp, env_lst->envm);
		if (!parser(tmp, env_lst))
		{
			re_free(str, tmp);
			str = minishell_gnl(fd);
			continue ;
		}
		ft_miniprocess(tmp, env_lst);
		re_free(str, tmp);
		str = minishell_gnl(fd);
	}
}
