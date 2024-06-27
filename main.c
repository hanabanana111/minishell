/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/27 20:17:29 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    setup_terminal(int n)
{
    struct termios    term;

    rl_outstream = stderr;
    if (isatty(STDIN_FILENO) == 0)
        return ;
    if (tcgetattr(STDIN_FILENO, &term) == -1)
        exit(-1);
    if (n == 0)
        term.c_lflag &= ~ECHOCTL;
    else
        term.c_lflag |= ECHOCTL;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
        exit(-1);
}

int main(void)
{
}