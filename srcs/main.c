/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/19 16:25:35 by hakobori         ###   ########.fr       */
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
	set_pwd(&status);
	status.exp = create_export(status.envm);
	treat_signal();
	treat_read(&status);
	ft_free_2d_array(status.envm);
	return (0);
}
