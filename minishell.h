/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 23:59:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/06/25 19:12:53 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <stdlib.h>
#include <stdio.h>
# include <unistd.h>
#include <string.h>

# define ERROR -1
// command or arg
# define ARG 1
// pipe
# define PIPE 2
// > or >>
# define RIGHT 3
// < or <<
# define LEFT 4
//infile
# define IN 5
//outfile
# define OUT 6

typedef struct s_info
{
	char *str;
	int	type;
	t_info *next;
} t_info;

#endif