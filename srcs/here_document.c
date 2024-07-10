/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/10 17:29:09 by hakobori         ###   ########.fr       */
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

static char	*re_create(char *str, char tmp)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(ft_strlen(str) + 2);
	if (ans == NULL)
		exit(1);
	i = -1;
	while (str[++i])
		ans[i] = str[i];
	ans[i] = tmp;
	ans[i + 1] = '\0';
	free(str);
	return (ans);
}

static char	*pipex_gnl(char *eof,t_status *status)
{
	char	*ans;
	char	tmp;
	int		len;

	ans = (char *)malloc(1);
	if (ans == NULL)
		exit(1);
	ans[0] = '\0';
	ft_printf("%s",pronpt_ps2(status->envm));
	len = 0;
	while (1)
	{
		read(0, &tmp, 1);
		len++;
		ans = re_create(ans, tmp);
		if (checker(ans, eof) != 0)
			break ;
		if (tmp == '\n')
			ft_printf("%s",pronpt_ps2(status->envm));
            // write(1, "> ", 2);
	}
	ans[len - ft_strlen(eof) - 1] = '\0';
	return (ans);
}

void	here_doc(t_info *cmd_info,t_status *status)
{
	// int		pipe1[2];
	// char	*str;
	t_info *node;
    //char    *pre;
	char *eof;

	node = cmd_info;
	while (node)
	{
		if (node->type == LEFT && !ft_strncmp(node->str,"<<\0",3)&& node->next)
		{
			//pre = node->str;
			eof = node->next->str;
			node->next->str = pipex_gnl(eof,status);
			node->next->str[s_strlen(node->next->str) - 2] = '\0';
			free(eof);
		}
		node = node->next;
	}
}
