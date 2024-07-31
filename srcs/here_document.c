/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/31 15:05:34 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(char *str, char *eof)
{
	if (ft_strncmp(str, eof, s_strlen(eof)) == 0)
	{
		if (str[s_strlen(eof)] == '\0')
			return (1);
	}
	return (0);
}

char	*join_n(char *ans)
{
	char	*pre;
	char	*ret;

	pre = ans;
	ret = ft_strjoin(pre, "\n");
	free(pre);
	return (ret);
}

void	init_variables(char **line, char **ans)
{
	*line = NULL;
	*ans = NULL;
}

char	*join_newline(char *ans, char *line)
{
	char	*pre;
	char	*ret;

	pre = ans;
	ret = ft_strjoin(pre, line);
	free(pre);
	ret = join_n(ret);
	free(line);
	return (ret);
}

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	char	*line;
	char	*pronpt;

	init_variables(&line, &ans);
	while (!g_sig)
	{
		pronpt = pronpt_ps2(status->envm);
		line = readline(pronpt);
		if (!line)
		{
			ft_printf(2,"%s: warning: here-document at line delimited by end-of-file (wanted `%s')\n",pronpt,eof);
			free(pronpt);
			break;
		}
		free(pronpt);
		if(g_sig == SIGINT)
			break ;
		if (checker(line, eof) != 0)
		{
			if (ans)
				ans = join_n(ans);
			break ;
		}
		ans = join_newline(ans, line);
	}
	return (ans);
}
