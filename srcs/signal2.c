/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:34:25 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/25 14:41:02 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_default(int signum)
{
	char	*pronpt;

	if (signal(signum, SIG_DFL) == SIG_ERR)
	{
		pronpt = pronpt_ps1(NULL);
		write(2, pronpt, s_strlen(pronpt));
		free(pronpt);
		write(2, &": ", 2);
		perror(strerror(errno));
	}
}

void	sig_default_all(void)
{
	sig_default(SIGINT);
	sig_default(SIGQUIT);
}

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
