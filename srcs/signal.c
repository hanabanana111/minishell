/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/28 18:28:56 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int signum)
{
	g_sig = (sig_atomic_t)signum;
	rl_on_new_line();
	rl_replace_line("", 1);
	write(2, "\n", 1);
	rl_redisplay();
}

void	set_handler_sigint(int signum)
{
	char	*pronpt;

	if (signal(signum, handler_sigint) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}

void	handler_sigquit(int signum)
{
	g_sig = (sig_atomic_t)signum;
}

void	set_handler_sigquit(int signum)
{
	char	*pronpt;

	if (signal(signum, handler_sigquit) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}

void	treat_signal(void)
{
	set_ignore(SIGQUIT);
	set_handler_sigint(SIGINT);
}

