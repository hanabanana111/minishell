/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/23 21:25:50 by hakobori         ###   ########.fr       */
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

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	char	*line;
	char	*pre_ans;
	static t_gnl gnl;
	char	*pronpt;

	pre_ans = NULL;
	line = NULL;
	ans = NULL;
	is_here_doc(1);
	ft_bzero(&gnl,sizeof(t_gnl));
	while (1)
	{
		pronpt = pronpt_ps2(status->envm);
		line = readline(pronpt);
		free(pronpt);
		if(!line)
			break;
		if (checker(line, eof) != 0)
		{
			if(ans)
			{
				pre_ans = ans;
				ans = ft_strjoin(pre_ans,"\n");
				free (pre_ans);
			}	
			break ;
		}
		pre_ans = ans;
		ans = ft_strjoin(pre_ans,line);
		pre_ans = ans;
		ans = ft_strjoin(pre_ans,"\n");
		free (pre_ans);
		free (line);
		if(g_sig == SIGINT)
		{
	printf("hello\n");
			g_sig = 0;
			break;
		}
	}

	is_here_doc(0);
	return (ans);
}
