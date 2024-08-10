/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:34:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/10 20:13:53 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_ignore(int signum)
{
	if (signal(signum, SIG_IGN) == SIG_ERR)
		perror(strerror(errno));
}

void	sig_ign_all(void)
{
	set_ignore(SIGINT);
	set_ignore(SIGQUIT);
}

void	handler_here_doc(int signum)
{
	g_sig = (sig_atomic_t)signum;
	// rl_on_new_line();
	write(STDIN_FILENO, "bbb\n", 4);
	close(0);
}

void	set_sigint_here_doc(int signum)
{
	if (signal(signum, handler_here_doc) == SIG_ERR)
		perror(strerror(errno));
}
