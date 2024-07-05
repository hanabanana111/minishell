/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/05 17:02:49 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig;

# define ERROR -1
# define TRUE 1
# define FALSE 0

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

// quotes
# define SINGLE_Q 1
# define DOUBLE_Q 2

typedef struct s_cmd
{
	char						*cmd;
	char						*path;
	char						**arg;
	int							*pipe_0;
	int							*pipe_1;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_info
{
	char						*str;
	int							type;
	int							is_quotes;
	struct s_info				*next;
}								t_info;

typedef struct s_status
{
	int							end_status;
	char						**envm;
}								t_status;

size_t							ft_strlen(const char *s);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
void							ft_miniprocess(t_info *lst, char **env);
int								determine_infile(char *cmd, char *next,
									int infile_fd);
void							error_exit(char *str);
t_cmd							*create_nord(void);
char							**set_args(char *str, char **args);
int								count_pipe(t_info *lst);
void							ft_free(char **str);

void							treat_read(t_status *status);
void							treat_signal(void);
void							to_new_pronpt(void);
void							treat_parser(char *line, t_status *status);
char							**split_to_token(char const *s, char *sep,
									t_status *status);
int								check_quotes(const char **str);
char							*format_quotes_and_strndup(char const *s,
									size_t n, t_status *status);
t_info							*treat_info_lst(char **arr);
t_info							*info_lstnew(char *cmd);
int								to_parse_lst(t_info **cmd_info);
char							*treat_doll(char const *str, t_status *status);
char							**treat_env(char **envm);
void							ft_free_2d_array(char **head);
#endif