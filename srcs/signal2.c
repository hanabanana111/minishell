/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:34:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/14 20:58:03 by hakobori         ###   ########.fr       */
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
	write(STDIN_FILENO, "\n", 1);
	close(0);
}

void	set_sigint_here_doc(int signum)
{
	if (signal(signum, handler_here_doc) == SIG_ERR)
		perror(strerror(errno));
}
