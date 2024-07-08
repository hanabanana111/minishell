/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/08 20:28:44 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_terminal(int n)
{
	struct termios	term;

	rl_outstream = stderr;
	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(1);
	if (n == 0)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(1);
}

void	treat_read(t_status *status)
{
	char	*line;
	t_info *cmd_info;

	line = NULL;
	setup_terminal(1);
	while (1)
	{
		line = readline("> ");
		if(g_sig)
			end_status_func(130);
		if (!line)
		{
			free(line);
			break ;
		}
		else if (*line)
		{
			cmd_info = lexer(line,status);
			parser(cmd_info,status);
			add_history(line);
		}
		free(line);
	}
	write(1, "exit", 4);
}
