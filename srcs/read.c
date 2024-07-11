/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/11 21:10:11 by hakobori         ###   ########.fr       */
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
	char	*tmp;
	t_info	*cmd_info;

	setup_terminal(1);
	while (1)
	{
		status->line = readline(pronpt_ps1(status->envm));
		tmp = status->line;
		if (g_sig)
			end_status_func(130);
		if (!status->line)
		{
			printf("pass !status->line\n");
			free(tmp);
			break ;
		}
		else if (*status->line)
		{
			cmd_info = lexer(status->line, status);
			parser(cmd_info, status);
			ft_miniprocess(cmd_info, status);
			//debug_print_lst(cmd_info);
			add_history(status->line);
		}
		free(tmp);
	}
	write(1, "exit", 4);
}
