/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/15 19:37:50 by hakobori         ###   ########.fr       */
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

void	set_readline_pronpt2(t_status *status, char **line)
{
	char	*pronpt;

	pronpt = pronpt_ps2(status->envm);
	*line = readline(pronpt);
	free(pronpt);
}

void	set_ans(char *line, size_t *len, char *ans)
{
	(*len) += s_strlen(line);
	ans[*len] = '\n';
	ans[(*len) + 1] = '\0';
	(*len)++;
	free(line);
}

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	size_t	len;
	char	*line;
	char	*pre_ans;

	len = 0;
	pre_ans = NULL;
	line = NULL;
	ans = NULL;
	while (1)
	{
		set_readline_pronpt2(status, &line);
		ans = (char *)ft_calloc(sizeof(char), len + s_strlen(line) + 2);
		if (!ans)
			return (free(line), NULL);
		if(ans && ans[0] == '\0')
		{
			// rl_num_chars_to_read = 1;
			// rl_event_hook = (void *)do_nothing(-1);
			break;
		}
		if (pre_ans)
			ft_strlcpy(ans, pre_ans, s_strlen(pre_ans) + 1);
		if(line)
			ft_strlcpy(ans + len, line, s_strlen(line) + 1);
		pre_ans = ans;
		if(!line)
			break;
		set_ans(line, &len, ans);
		if (checker(ans, eof) != 0)
			break ;
	}
	ans[len - ft_strlen(eof)] = '\0';
	return (ans);
}
