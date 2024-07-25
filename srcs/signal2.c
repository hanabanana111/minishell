/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:34:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/25 17:37:20 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_ignore(int signum)
{
	char	*pronpt;

	if (signal(signum, SIG_IGN) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}

void	sig_ign_all(void)
{
	set_ignore(SIGINT);
	set_ignore(SIGQUIT);
}


void	handler_here_doc(int signum)
{
	g_sig = (sig_atomic_t)signum;
	rl_on_new_line();
	rl_replace_line("", 1);
	write(2, "\n", 1);
}

void	set_sigint_here_doc(int signum)
{
	char	*pronpt;

	if (signal(signum, handler_here_doc) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}