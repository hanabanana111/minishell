/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:10:53 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/23 22:47:19 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_new_pronpt(void)
{
	if(set_get_readline(NULL) && !ft_strncmp("cat\0",set_get_readline(NULL),4))
	{
		write(STDOUT_FILENO, "\n", 1);
		set_get_readline("");
	}
	else if(is_here_doc(-1))
	{
		// printf("pass");
	}
	else
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

void sig_set_ignore(int signum)
{
	char *pronpt;
	
	if (signal(signum, SIG_IGN) == SIG_ERR)
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
