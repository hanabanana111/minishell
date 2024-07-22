/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:34:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/20 22:05:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_reset(int signum)
{
	// struct sigaction sa;
	char *pronpt;
	
	// sigemptyset(&sa.sa_mask);	
	// sa.sa_handler = SIG_DFL;
	if(signal(signum, SIG_DFL) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}

void sig_reset_all(void)
{
	sig_reset(SIGINT);
	sig_reset(SIGQUIT);
}
void sig_ign_all(void)
{
	sig_set_ignore(SIGINT);
	sig_set_ignore(SIGQUIT);
}