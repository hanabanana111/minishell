/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fce.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:14:49 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/19 14:29:26 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fce(char *str, int fd, t_cmd *lst)
{
	free_cmd(lst);
	free(str);
	close(fd);
	exit(end_status_func(-1));
}
