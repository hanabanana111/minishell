/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:18:51 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/20 10:23:47 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_args_print_error(char *arg1)
{
	ft_printf(2, "env: ‘%s’: No such file or directory\n", arg1);
	end_status_func(127);
}
