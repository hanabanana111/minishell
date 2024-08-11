/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/11 17:22:47 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(char *line, char *eof, char **ans)
{
	if (ft_strncmp(line, eof, s_strlen(eof)) == 0)
	{
		if (line[s_strlen(eof)] == '\0')
		{
			if (*ans)
				*ans = join_n(*ans);
			free (line);
			return (TRUE);
		}
	}
	return (FALSE);
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
	int	fd;

	fd = dup(STDIN_FILENO);
	set_get_std_in(fd);
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
	char		*ans;
	char		*line;
	char		*pronpt;
	static t_buf	bufs;

	init_variables(&line, &ans);
	while (!g_sig)
	{
		pronpt = pronpt_ps2(status->envm);
		write(1,pronpt,ft_strlen(pronpt));
		line = get_next_line(0, &bufs);
		free(pronpt);
		if (g_sig == SIGINT)
			break ;
		if (!line)
		{
			write(1,"\n",1);
			break;
		}
		if (checker(line, eof, &ans) != 0)
			break ;
		ans = join_newline(ans, line);
	}
	return (ans);
}
