/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/23 19:47:57 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*do_nothing(int i)
{
	(void)i;
	return (NULL);
}

void	to_new_pronpt(void)
{
	if(set_get_readline(NULL) && !ft_strncmp("cat\0",set_get_readline(NULL),4))
	{
		write(STDOUT_FILENO, "\n", 1);
		set_get_readline("");
		return;
	}
	else if(is_here_doc(-1))
	{
		// rl_on_new_line();
		// rl_done = 1;
		// write(STDOUT_FILENO, "\n", 1);
		// rl_redisplay();
	}
	else if(set_get_readline(NULL))
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	// printf("pass\n");
}

void	signal_handler_sigint(int signum)
{
	g_sig = (sig_atomic_t)signum;
	to_new_pronpt();
}

void	treat_signal(void)
{
	if (signal(SIGINT, (void *)signal_handler_sigint))
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
