/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 14:46:06 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }

int	main(int argc, char *argv[], char **env)
{
	t_status	status;

	if (argc > 1)
		return (0);
	(void)argv;
	end_status_func(0);
	ft_bzero(&status, sizeof(t_status));
	status.envm = treat_env(env);
	treat_signal();
	treat_read(&status);
	ft_free_2d_array(status.envm);
	return (0);
}
