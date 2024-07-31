/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/31 13:51:35 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int signum)
{
	g_sig = (sig_atomic_t)signum;
	end_status_func(130);
	rl_on_new_line();
	rl_replace_line("", 1);
	write(2, "\n", 1);
	rl_redisplay();
}

void	set_handler_sigint(int signum)
{
	if (signal(signum, handler_sigint) == SIG_ERR)
		perror(strerror(errno));
}

void	handler_sigquit(int signum)
{
	g_sig = (sig_atomic_t)signum;
}

void	set_handler_sigquit(int signum)
{
	if (signal(signum, handler_sigquit) == SIG_ERR)
		perror(strerror(errno));
}

void	treat_signal(void)
{
	set_ignore(SIGQUIT);
	set_handler_sigint(SIGINT);
}
