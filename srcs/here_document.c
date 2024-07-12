/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/12 15:20:50 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_eof(char *eof)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(eof) + 3);
	if (ans == NULL)
		exit(1);
	ans[0] = '\n';
	i = 1;
	while (eof[i - 1])
	{
		ans[i] = eof[i - 1];
		i++;
	}
	ans[i++] = '\n';
	ans[i] = '\0';
	return (ans);
}

static int	checker(char *str, char *eof)
{
	int		i;
	char	*new_eof;

	i = 0;
	new_eof = ft_eof(eof);
	if (ft_strncmp(str, eof, ft_strlen(eof)) == 0)
	{
		if (str[ft_strlen(eof)] == '\n')
		{
			free(new_eof);
			return (1);
		}
	}
	while (str[i])
	{
		if (ft_strncmp(&str[i], new_eof, ft_strlen(new_eof)) == 0)
		{
			free(new_eof);
			return (1);
		}
		i++;
	}
	free(new_eof);
	return (0);
}

void	set_readline(t_status *status, char *pronpt, char *line)
{
	pronpt = pronpt_ps2(status->envm);
	line = readline(pronpt);
	free(pronpt);
}

void	set_ans(char *line, size_t *len)
{
	(*len) += s_strlen(line);
	ans[*len] = '\n';
	ans[(*len) + 1] = '\0';
	(*len)++;
	free(line);
}

static char	*pipex_gnl(char *eof, t_status *status)
{
	char	*ans;
	size_t	len;
	char	*pronpt;
	char	*line;
	char	*pre_ans;

	len = 0;
	pre_ans = NULL;
	while (1)
	{
		set_readline(status, pronpt, line);
		ans = (char *)ft_calloc(sizeof(char), len + s_strlen(line) + 2);
		if (!ans)
			return (free(line), NULL);
		if (pre_ans)
			ft_strlcpy(ans, pre_ans, s_strlen(pre_ans) + 1);
		ft_strlcpy(ans + len, line, s_strlen(line) + 1);
		pre_ans = ans;
		set_ans(line, &len);
		if (checker(ans, eof) != 0)
			break ;
	}
	ans[len - ft_strlen(eof)] = '\0';
	return (ans);
}
