/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/23 20:57:42 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_new_pronpt(void)
{
	if(set_get_readline(NULL) && !ft_strncmp("cat\0",set_get_readline(NULL),4))
	{
		printf("pass1\n");
		write(STDOUT_FILENO, "\n", 1);
		set_get_readline("");
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
		printf("pass3\n");
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

void sig_set_ignore(int signum)
{
	if (signal(SIGINT, (void *)signal_handler_sigint))
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}
void sig_set_handler(int signum)
{
	char *pronpt;
	
	
	if(signal(signum, signal_handler_sigint) == SIG_ERR)
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
	sig_set_ignore(SIGQUIT);
	sig_set_handler(SIGINT);
}
