/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:27:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/12 15:36:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*re_create(char *str, char tmp)
{
	char	*ans;
	int		i;
	int		j;

	ans = (char *)malloc(ft_strlen(str) + 2);
	if (ans == NULL)
		exit(1);
	i = 0;
	j = 0;
	while (str[i])
		ans[j++] = str[i++];
	ans[j] = tmp;
	ans[j + 1] = '\0';
	free(str);
	return (ans);
}

int	ans_checker(char *ans)
{
	size_t	i;

	i = 0;
	while (ans[i])
	{
		if (ans[i] != '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static char	*pipex_gnl(t_status *status)
{
	char	*ans;
	char	tmp;
	int		len;

	ans = (char *)malloc(1);
	if (ans == NULL)
		exit(1);
	ans[0] = '\0';
	ft_printf("%s", pronpt_ps2(status->envm));
	len = 0;
	while (1)
	{
		read(0, &tmp, 1);
		len++;
		ans = re_create(ans, tmp);
		if (tmp == '\n' && !ans_checker(ans))
			ft_printf("%s", pronpt_ps2(status->envm));
		else if (tmp == '\n')
			break ;
	}
	ans[len - 1] = '\0';
	return (ans);
}

char	*s_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, " ", 2);
	ft_strlcpy(result + s1_len + 1, s2, s2_len + 1);
	return (result);
}

void	here_doc_pipe(t_info *cmd_info, t_status *status)
{
	char	*new_line;
	char	*pre;
	t_info	*node;
	t_info	*new;

	node = cmd_info;
	if (status->is_pipe_syntax || status->is_redi_syntax)
		return ;
	while (node->next)
		node = node->next;
	if (node->type == PIPE && !node->next)
	{
		new_line = pipex_gnl(status);
		pre = status->line;
		status->line = s_strjoin(status->line, new_line);
		new = lexer(new_line, status);
		node->next = new;
		new->pre = node;
		free(pre);
	}
	else
		return ;
	here_doc_pipe(cmd_info, status);
}
