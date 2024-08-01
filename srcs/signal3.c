/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:09:13 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/01 15:18:10 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_minishell(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 10)
		return (FALSE);
	len -= 10;
	if (!ft_strncmp(&path[len], "/minishell", 11))
		return (TRUE);
	return (FALSE);
}

void	handler_status(int signum)
{
	if (signum == SIGINT)
		end_status_func(130);
	else if (signum == SIGQUIT)
		end_status_func(131);
	if (!is_pipe_exist(NULL))
	{
		if (signum == SIGQUIT)
			ft_printf(2, "Quit (core dumped)");
		write(1, "\n", 1);
	}
}

void	set_sig_status(int signum)
{
	if (signal(signum, handler_status) == SIG_ERR)
		perror(strerror(errno));
}

void	sig_status_all(void)
{
	set_sig_status(SIGINT);
	set_sig_status(SIGQUIT);
}
