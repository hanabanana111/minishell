/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/12 14:08:48 by hakobori         ###   ########.fr       */
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

static char	*pipex_gnl(char *eof,t_status *status)
{
	char	*ans;
	size_t		len;
	char *pronpt;
	char *line;
	char *pre_ans;

	len = 0;
	pre_ans = NULL;
	while (1)
	{
		pronpt = pronpt_ps2(status->envm);
		line = readline(pronpt);
		free(pronpt);
		ans = (char *)ft_calloc(sizeof(char),len + s_strlen(line) + 2);
		if(!ans)
			return(free(line),NULL);
		if(pre_ans)
			ft_strlcpy(ans , pre_ans ,s_strlen(pre_ans) + 1);
		ft_strlcpy(ans + len , line ,s_strlen(line) + 1);
		pre_ans = ans;
		len += s_strlen(line);
		ans[len] = '\n';
		ans[len + 1] = '\0';
		len++;
		free(line);
		if (checker(ans, eof) != 0)
			break ;
	}
	ans[len - ft_strlen(eof)] = '\0';
	return (ans);
}

void set_here_doc_env_value(t_info *node,t_status *status)
{
	size_t i;
	t_env_quote_info	e_q_info;

	i = 0;
	ft_bzero(&e_q_info, sizeof(t_env_quote_info));
	while (node->str[i])
	{
		if(node->str[i] == '$')
		{
			treat_doll(&node->str[++i], &e_q_info);
			find_env(&e_q_info, status->envm);
			ft_chenge_env_to_value(node, &e_q_info);
		}
		i++;
	}
}

void	here_doc(t_info *cmd_info,t_status *status)
{
	t_info *node;
	char *eof;

	node = cmd_info;
	while (node)
	{
		if (node->type == LEFT && !ft_strncmp(node->str,"<<\0",3)&& node->next)
		{
			eof = node->next->str;
			node->next->str = pipex_gnl(eof,status);
			node->next->str[s_strlen(node->next->str) - 1] = '\0';
			if(!node->next->is_quote)
				set_here_doc_env_value(node->next,status);
			free(eof);
		}
		node = node->next;
	}
}
