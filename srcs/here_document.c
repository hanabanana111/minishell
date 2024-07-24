/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/24 21:01:30 by hakobori         ###   ########.fr       */
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

void init_variables(char **pre_ans, char **line, char **ans, t_gnl *gnl)
{
	*pre_ans = NULL;
	*line = NULL;
	*ans = NULL;
	ft_bzero(gnl,sizeof(t_gnl));
}

// void	
// {
// 	pre_ans = ans;
// 	ans = ft_strjoin(pre_ans,line);
// 	ans = join_n(ans);
// 	free (line);
// }

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	char	*line;
	char	*pre_ans;
	static t_gnl gnl;
	char	*pronpt;

	init_variables(&pre_ans, &line, &ans, &gnl);
	is_here_doc(1);
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
				ans = join_n(ans);
			break ;
		}
		pre_ans = ans;
		ans = ft_strjoin(pre_ans,line);
		ans = join_n(ans);
		free (line);
		if(g_sig == SIGINT)
		{
			free(ans);
			ans = NULL;
			break;
		}
	}
	is_here_doc(0);
	return (ans);
}
