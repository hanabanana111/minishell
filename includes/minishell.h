/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/02 13:31:42 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

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

# define SINGLE 1
# define DOUBLE 2

typedef struct s_cmd
{
	char						*cmd;
	char						*path;
	char						**arg;
	int							pipe_0;
	int							pipe_1;
	char						*error_file;
	char						*error_str;
	struct s_cmd				*pre;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_info
{
	char						*str;
	char						*key;
	int							type;
	int							flg;
	int							e_flg;
	char						*errstr;
	int							len;
	int							is_quote;
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
	char						**exp;
	char						**envm;
	char						*pwd;
	char						*home;
	int							is_pipe_syntax;
	int							is_redi_syntax;
	char						*line;
}								t_status;

typedef struct s_syntax_heredoc
{
	int							is_syntax;
	int							is_heredoc;
}								t_syn_here;

typedef struct s_gnl
{
	char						buf[42];
	char						*bufp;
	int							n;
}								t_gnl;

void							ft_miniprocess(t_info *first,
									t_status *env_lst);
t_info							*infile_fd(t_cmd *cmd_lst, t_info *lst);
void							error_exit(char *str);
t_cmd							*create_nord(t_info *lst);
char							**set_args(char *str, char **args);
int								count_pipe(t_info *lst);
void							ft_free(char **str);
t_cmd							*create_lst(t_info *lst);
t_cmd							*path_finder(t_cmd *ans, char **env);
char							*search_env(char *cmd, char **env);
t_info							*outfile_fd(t_cmd *cmd_lst, t_info *lst);
t_cmd							*create_pipe(t_cmd *cmd_lst, t_info *lst);
void							parent_process(t_cmd *lst, int i);
char							*ft_strjoin2(char *s1, char *s2);
t_info							*decide_file(t_info *first);
void							children_process(t_cmd *lst, t_status *env_lst,
									t_cmd *first);
void							parent_process(t_cmd *lst, int i);
void							ft_close(t_cmd *first);
void							re_process(t_cmd *lst, t_status *env_lst);
void							treat_read(t_status *status);
void							treat_signal(void);
void							to_new_pronpt(void);
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
void							treat_doll(char const *str,
									t_env_quote_info *e_q_info, t_info *node);
void							find_env(t_env_quote_info *e_q_info,
									char **envm);
void							ft_chenge_env_to_value(t_info *node,
									t_env_quote_info *e_q_info);
void							format_quote(t_info **cmd_lst);
int								end_status_func(int status);
size_t							s_strlen(char *str);
void							set_arr_to_lst(char **arr, t_info **cmd_lst);
void							check_env(t_info **cmd_lst, char **envm);
void							separator(t_info **cmd_info);
char							*ft_strndup(char const *s, size_t n);
char							*pronpt_ps1(char **env);
char							*pronpt_ps2(char **env);
char							*get_value(char **env, char *key);
void							here_doc(t_info *cmd_info, t_status *status);
void							here_doc_pipe(t_info *cmd_info,
									t_status *status);
void							is_syntax2(t_info *cmd_info, t_status *status);
void							parser(t_info *cmd_info, t_status *status);
int								is_here_document(t_info *cmd_info);
void							set_lst_details(t_info **cmd_info, char **envm);
void							debug_print_lst(t_info *cmd_info);
t_info							*lexer(char *line, t_status *status);
void							set_here_doc_env_value(t_info *node,
									t_status *status);
void							here_doc(t_info *cmd_info, t_status *status);
char							*pipex_gnl_rd(char *eof, t_status *status);
void							set_token_types(t_info **cmd_info);
void							show_syntax_error(char *str, t_info *node);
int								is_syntax_error1(t_info *node,
									t_status *status);
int								is_syntax_error1_true_false(t_info *node);
void							is_syntax1(t_info *cmd_info, t_status *status);
int								is_syntax_error2(t_info *node);
char							*delete_quotes_and_strndup(char *src, size_t n,
									t_info *node);
void							separate_cmd(char *cmd, t_info *node,
									size_t *j);
int								is_here_doc(int num);
void							*do_nothing(int i);
int								echo_func(t_cmd *lst);
int								built_in(t_cmd *lst, t_status *status);
int								ft_strcmp(char *str1, char *str2);
char							*expdup2(char *ans, char *tmp);
char							**create_export(char **env);
char							**remove_exp(char **exp, char *str);
int								ft_len(char **exp);
int								ft_lstlen(t_cmd *first);
int								check_exp(char **exp, char *str);
char							*key_format(char *str);
int								change_key_value(t_status *status, char *key,
									char *new, int is_plus);
int								add_env(t_status *status, char *new);
int								find_i_of_key(char *key, char **env);
char							*ft_strtrim2(char *str, int index);
char							**plus_eq_exp(char **exp, char *str);
int								export_func(char **arg, t_status *status,
									t_cmd *first);
int								builtin2(t_cmd *lst, t_status *status);
int								pwd_func(t_status *status);
int								is_join(char *key);
char							*format_value(char *env, char *key);
char							**eq_exp(char **exp, char *str);
char							**add_export(char **exp, char *str);
int								export_func2(char **arg, t_status *status,
									t_cmd *first);
void							print_export(char **exp);
int								check_builtin(char *cmd);
void							ft_expjoin2(char *tmp, char *ans, int index,
									char *str);
int								check_eq2(char *tmp);
char							*ft_expstr(char *tmp, char *tmp2);
int								env_func(char **env, t_cmd *lst);
int								exit_func(t_cmd *lst, int is_parents,
									t_status *status);
int								set_pwd_init(t_status *status);
int								set_home(t_status *status);
void							change_oldpwd(t_status *status, char *old_path);
char							**remove_env(char **env, char *key);
char							**replace_home(char **arg, t_status *status);
int								ft_cd(t_cmd *first, t_status *status);
void							change_pwd(t_status *status, char *path);
char							*ft_pwddup(void);
int								unset_func(t_status *status, t_cmd *first);
int								check_env_path(char **env);
void							sig_default(int signum);
void							sig_default_all(void);
void							set_ignore(int signum);
void							sig_ign_all(void);
void							set_handler_sigint(int signum);
char							*re_pwd(t_status *status, char *str);
void							ft_free_paths(int i, char **paths);
void							print_s1(char **env);
void							free_cmd(t_cmd *lst);
void							re_free(char *str, t_info *lst);
void							set_sigint_here_doc(int signum);
void							set_sigint_child(int signum);
void							sig_child(int signum);
int								is_execve(int num);
void							perror_s1(char **env);
int								printf_error_cd(char **env, t_cmd *lst);
int								printf_error_cd2(char *path, char **env);
int								printf_error_cd3(char **env);
void							set_handler_sigquit(int signum);
void							sig_status_all(void);
int								is_minishell(char *path);
int 							set_get_std_in(int fd);
int								write_error_str(t_status *status,char *str);
int 							is_pipe_exist(t_info *cmd_info);
void							free_t_info(t_info **cmd_info);

void							debug_print_lst(t_info *cmd_info);
#endif