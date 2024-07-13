/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:13:06 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/13 17:10:49 by hakobori         ###   ########.fr       */
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

void	is_line(t_status *status, t_info *cmd_info)
{
	cmd_info = lexer(status->line, status);
	if(!cmd_info)
		return;
	parser(cmd_info, status);
	// debug_print_lst(cmd_info);
	if (!status->is_pipe_syntax && !status->is_redi_syntax)
		ft_miniprocess(cmd_info, status);
	// printf("%d\n", cmd_info -> e_flg);
	// if (cmd_info -> e_flg == 1)
	// 	exit(0);
	add_history(status->line);
}

void	treat_read(t_status *status)
{
	char	*tmp;
	t_info	*cmd_info;
	char	*pronpt;

	cmd_info = NULL;
	setup_terminal(1);
	while (1)
	{
		pronpt = pronpt_ps1(status->envm);
		status->line = readline(pronpt);
		set_get_readline(status->line);
		free(pronpt);
		tmp = status->line;
		if (g_sig)
			end_status_func(130);
		if (!status->line)
		{
			free(tmp);
			break ;
		}
		else if (*status->line)
			is_line(status, cmd_info);
	}
	write(1, "exit\n", 5);
}
