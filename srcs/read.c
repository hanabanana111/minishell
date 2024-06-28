/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/28 22:41:53 by hakobori         ###   ########.fr       */
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

void	treat_read(void)
{
	char	*line;

	line = NULL;
	setup_terminal(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, "exit\n", 5))
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
