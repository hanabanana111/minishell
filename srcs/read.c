/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 14:23:08 by hakobori         ###   ########.fr       */
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
	int	is_paesed;

	line = NULL;
	setup_terminal(1);
	while (1)
	{
		is_paesed = 0;
		line = readline("> ");
		if (!line)// || !ft_strncmp(line, "exit\n", 5)
		{
			free(line);
			break ;
		}
		else if (*line)
		{
			treat_parser(line,&is_paesed);
			if(is_paesed)
				add_history(line);
		}
		free(line);
	}
	write(1, "exit", 4);
}
