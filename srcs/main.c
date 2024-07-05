/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 17:01:23 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

int	main(int argc, char *argv[], char **env)
{
	t_status	status;

	// int	end_status;
	if (argc > 1)
		return (0);
	(void)argv;
	status.end_status = 0;
	status.envm = treat_env(env);
	// int i = 0;
	// while(status.envm[i])
	// {
	// 	printf("%s\n",status.envm[i++]);
	// }
	treat_signal();
	treat_read(&status);
	ft_free_2d_array(status.envm);
	return (0);
}
