/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/06 09:40:34 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

//volatile sig_atomic_t	g_sig = 0;

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
	char				*str;
	int					type;
	char				*errstr;
	int					flg;
	struct s_info		*next;
}						t_info;

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

#endif