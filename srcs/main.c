/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/28 05:00:49 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_sigint(int signum)
{
    (void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

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

void	treat_read(void)
{
	char	*line;

	line = NULL;
    setup_terminal(1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);
			break ;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	write(1, "exit", 4);
}

void treat_signal(void)
{
	if (signal(SIGINT, signal_handler_sigint) == SIG_ERR)
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

int	main(void)
{
    treat_signal();
	treat_read();
	return (0);
}
