/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/26 20:04:21 by rkawahar         ###   ########.fr       */
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

// command or arg
# define ARG 1
// pipe
# define PIPE 2
// > or >>
# define RIGHT 3
// < or << or <<<
# define LEFT 4
//infile
# define IN 5
//outfile
# define OUT 6

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