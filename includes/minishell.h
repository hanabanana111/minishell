/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/11 17:05:03 by hakobori         ###   ########.fr       */
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
// < or << 
# define LEFT 2
// infile
# define IN 3
// outfile
# define OUT 4
// cmd
# define CMD 5
// option or arg
# define OPT 6
// //<>
// # define LEFT_RIGHT 7

#define SINGLE 1
#define DOUBLE 2

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			**arg;
	int				pipe_0;
	int				pipe_1;
	char			*error_file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info
{
	char						*str;
	int							type;
	int 						flg;
	int							e_flg;
	char 						*errstr;
	int							len;
	int is_quote;
	struct s_info				*pre;
	struct s_info				*next;
}								t_info;

typedef struct s_env_quote_info
{
	char						q_chr;
	int							q_count;
	int							is_question;
	char						*key;
	char						*value;
}								t_env_quote_info;

typedef struct s_status
{
	char	**exp;
	char						**envm;
	int		is_pipe_syntax;
	int		is_redi_syntax;
	char *line;
}								t_status;

typedef struct s_syntax_heredoc
{
	int is_syntax;
	int is_heredoc;
}	t_syn_here;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_miniprocess(t_info *lst, char **env, int *status);
t_info	*infile_fd(t_cmd *cmd_lst, t_info *lst);
void	error_exit(char *str);
t_cmd	*create_nord(void);
char	**set_args(char *str, char **args);
int		count_pipe(t_info *lst);
void	ft_free(char **str);
char	*relative_path(t_cmd *lst);
t_cmd	*create_lst(t_info *lst);
t_cmd	*path_finder(t_cmd *lst, char **env);
char	*search_env(char *cmd, char **env);
t_info	*outfile_fd(t_cmd *cmd_lst, t_info *lst);
t_cmd	*create_pipe(t_cmd *cmd_lst, t_info *lst);
void	parent_process(t_cmd *lst, int i);
void	children_process(t_cmd *lst, char **env, t_cmd *first, t_info *info_lst);
char	*ft_strjoin2(char *s1, char *s2);
void	ft_echo(char **args);
void	ft_cd(char **args, char **env);
void	ft_pwd(char **env);
char	*export_str(char *str);
int		ft_strcmp(char *s1,char *s2);

void							treat_read(t_status *status);
void							treat_signal(void);
void							to_new_pronpt(void);
void							parser(t_info *cmd_info,
									t_status *status);
t_info							*lexer(char *line, t_status *status);
char							**split_to_token(char const *s, char *sep);
int								check_quotes(const char **str);
char							*consider_quotes_and_strndup(char const *s,
									size_t n);
t_info							*treat_info_lst(char **arr, t_status *status);
t_info							*info_lstnew(char *cmd);
int								to_parse_lst(t_info **cmd_info);
char							**treat_env(char **envm);
void							ft_free_2d_array(char **head);
void							treat_doll(char const *str, t_env_quote_info *e_q_info);
void							find_env(t_env_quote_info *e_q_info,
									t_status *status);
void							ft_chenge_env_to_value(t_info *node,
									t_env_quote_info *e_q_info);
void							format_quote(t_info **cmd_lst);
int end_status_func(int status);
size_t	s_strlen(char *str);
void	set_arr_to_lst(char **arr, t_info **cmd_lst);
void	check_env(t_info *cmd_lst, t_status *status);
void separator(t_info *cmd_info);
char	*ft_strndup(char const *s, size_t n);
const char	*pronpt_ps1(char **env);
const char	*pronpt_ps2(char **env);
char *get_value(char **env,char *key);
void	here_doc(t_info *cmd_info,t_status *status);
void	here_doc_pipe(t_info *cmd_info,t_status *status);

void debug_print_lst(t_info *cmd_info);
#endif
