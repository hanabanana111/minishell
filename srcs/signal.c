/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/15 19:45:01 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *do_nothing(int i)
{
	(void)i;
	return(NULL);
}

void	to_new_pronpt(void)
{
	if(is_here_doc(-1))
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// rl_num_chars_to_read = 1;
		// rl_event_hook = (void *)do_nothing(-1);
		//write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_sigint(int signum)
{
	g_sig = (sig_atomic_t)signum;
	to_new_pronpt();
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
