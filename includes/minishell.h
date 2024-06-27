/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/28 05:14:37 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

# define ERROR -1

// pipe
# define PIPE 0
// > or >>
# define RIGHT 1
// < or << or <<<
# define LEFT 2
// infile
# define IN 3
// outfile
# define OUT 4
// cmd
# define CMD 5
// option or arg
# define OPT 6
//<>
# define LEFT_RIGHT 7

typedef struct s_info
{
	char				*str;
	int					type;
	struct s_info		*next;
}						t_info;

size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
void					ft_prosses(t_info *lst, char **env);
int						determine_infile(t_info *lst);
void					error_exit(char *str);

// read.c
void					treat_read(void);

// signal.c
void					treat_signal(void);
#endif