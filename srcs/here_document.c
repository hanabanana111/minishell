/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/25 12:57:24 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker(char *str, char *eof)
{
	int		i;

	i = 0;
	if (ft_strncmp(str, eof, s_strlen(eof)) == 0)
	{
		if (str[s_strlen(eof)] == '\0')
			return (1);
	}
	return (0);
}

char *join_n(char *ans)
{
	char *pre;
	char *ret;

	pre = ans;
	ret = ft_strjoin(pre,"\n");
	free(pre);
	return(ret);
}

void init_variables(char **line, char **ans)
{
	*line = NULL;
	*ans = NULL;
}

char	*join_newline(char *ans, char *line)
{
	char *pre;
	char *ret;
	
	pre = ans;
	ret = ft_strjoin(pre,line);
	free(pre);
	ret = join_n(ret);
	free (line);
	return (ret);
}

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	char	*line;
	char	*pronpt;

	init_variables(&line, &ans);
	while (1)
	{
		pronpt = pronpt_ps2(status->envm);
		if (g_sig != SIGINT)
			line = readline(pronpt);
		free(pronpt);
		if(!line || g_sig == SIGINT)
		{
			free(ans);
			ans = NULL;
			break;
		}
		if (checker(line, eof) != 0)
		{
			if(ans)
				ans = join_n(ans);
			break ;
		}
		ans = join_newline(ans, line);
	}
	return (ans);
}
