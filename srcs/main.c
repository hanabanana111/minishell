/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/27 21:07:52 by hakobori         ###   ########.fr       */
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

void treat_read(char *line)
{
    setup_terminal(0);
    while(1)
    {
        line = readline("> ");
        if(!line)
        {
            free(line);
            break;
        }
        add_history(line);
        free(line);
    }
    write(1,"exit",4);
}

int main(void)
{
    char *line;
    line = NULL;
    treat_read(line);
    return(0);
}