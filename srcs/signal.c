/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/13 16:58:37 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_new_pronpt(void)
{
	char *tmp;
	tmp = set_get_readline(NULL);
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	if(!tmp || (ft_strncmp(tmp,"cat\0",4) && ft_strncmp(tmp,"grep",4)))
		rl_redisplay();
}

void	signal_handler_sigint(int signum)
{
	to_new_pronpt();
	g_sig = (sig_atomic_t)signum;
}

void	treat_signal(void)
{
	if (signal(SIGINT, (void (*)(int))signal_handler_sigint) == SIG_ERR)
	{
		perror(strerror(errno));
		exit(1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror(strerror(errno));
		exit(1);
	}
}
