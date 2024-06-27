/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/27 19:09:52 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# define ERROR -1

// command
# define ARG 1
// option
# define PIPE 2
// > or >>
# define RIGHT 3
// < or <<
# define LEFT 4
//infile(here_doc -> str)
# define IN 5
//outfile
# define OUT 6
//pipe
# define 
typedef struct s_info
{
	char	*str;
	int		type;
	t_info	*next;
}	t_info;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_prosses(t_info *lst, char **env);
int		determine_infile(t_info *lst);
void	error_exit(char *str);

#endif