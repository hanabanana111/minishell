/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/03 13:26:02 by kawaharadar      ###   ########.fr       */
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
	int				*pipe_0;
	int				*pipe_1;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info
{
	char				*str;
	int					type;
	struct s_info		*next;
}						t_info;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_miniprocess(t_info *lst, char **env);
int		determine_infile(char *cmd, char *next, int infile_fd);
void	error_exit(char *str);
t_cmd	*create_nord(void);
char	**set_args(char *str, char **args);
int		count_pipe(t_info *lst);
void	ft_free(char **str);
char	*relative_path(t_cmd *lst);

#endif