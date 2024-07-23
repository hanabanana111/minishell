/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:12:16 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/23 20:54:18 by kawaharadar      ###   ########.fr       */
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
	// printf("eof = [%s]\n", eof);
	// printf("str = [%s]\n", str);
	if (ft_strncmp(str, eof, ft_strlen(eof)) == 0)
	{
		if (str[ft_strlen(eof)] == '\0')
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

void	set_pronpt2(t_status *status)
{
	char	*pronpt;

	pronpt = pronpt_ps2(status->envm);
	write(1, pronpt, s_strlen(pronpt));
	free(pronpt);
}

void	set_ans(char *line, size_t *len, char *ans)
{
	size_t i;
	
	i = 0;
	if(!line)
		return ;
	while(line[i])
		ans[(*len)++] = *line++;
	(*len) += s_strlen(line);
}


static int	ft_getchar(int fd, t_gnl *gnl)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		return(-3);
	}
	if (gnl->n == 0)
	{
		gnl->n = read(fd, gnl->buf, 42);
		if (gnl->n < 0)
		{
			ft_bzero(gnl,sizeof(t_gnl));
			return (perror(strerror(errno)), -2);
		}
		gnl->bufp = gnl->buf;
	}
	if (--gnl->n >= 0)
		return ((unsigned char)*gnl->bufp++);
	else
	{
		ft_bzero(gnl,sizeof(t_gnl));
		return (EOF);
	}
}

char	*get_next_line(int fd, t_gnl *gnl)
{
	char	*first;
	char	*result;
	char	str[2];
	char	c;

	result = NULL;
	first = NULL;
	ft_bzero(&str,sizeof(str));
	while (fd >= 0)
	{
		first = result;
		c = ft_getchar(fd, gnl);
		if (c == EOF || c == -3)
			break ;
		if (c == -2)
			return (free(result), NULL);
		str[0] = c;
		result = ft_strjoin(result, str);
		if (!result)
			return (free(first), NULL);
		free(first);
		if (c == '\n')
			break ;
	}
	return (result);
}

char	*pipex_gnl_rd(char *eof, t_status *status)
{
	char	*ans;
	size_t	len;
	char	*line;
	char	*pre_ans;
	static t_gnl gnl;

	len = 0;
	pre_ans = NULL;
	line = NULL;
	ans = NULL;
	// rl_catch_signals = 1;
	while (1)
	{
		set_readline_pronpt2(status, &line);
		// if(!line)
		// write(1 ,"\n", 1);
			break;
		ans = (char *)ft_calloc(sizeof(char), len + s_strlen(line) + 2);
		if (!ans)
			return (free(line), NULL);
		if (pre_ans)
			ft_strlcpy(ans, pre_ans, s_strlen(pre_ans) + 1);
		if(line)
			ft_strlcpy(ans + len, line, s_strlen(line) + 1);
		pre_ans = ans;
		set_ans(line, &len, ans);
		// size_t (i) = 0;
		// while(line[i])
		// 	ans[len++] = *line++;
		// len += s_strlen(line);
		if (checker(ans, eof) != 0)
			break ;
		if(!line)
		{
			write(1, "\n", 1);
			break;
		}
		
	}
	// printf("pass\n");
	if(ans)
		ans[len - ft_strlen(eof)] = '\0';
	// is_here_doc(0);
	// sig_set_handler(SIGINT);
	return (ans);
}

// static char	*ft_eof(char *eof)
// {
// 	char	*ans;
// 	int		i;

// 	ans = (char *)malloc(ft_strlen(eof) + 3);
// 	if (ans == NULL)
// 		exit(1);
// 	ans[0] = '\n';
// 	i = 1;
// 	while (eof[i - 1])
// 	{
// 		ans[i] = eof[i - 1];
// 		i++;
// 	}
// 	ans[i++] = '\n';
// 	ans[i] = '\0';
// 	return (ans);
// }

// static int	checker(char *str, char *eof)
// {
// 	int		i;
// 	char	*new_eof;

// 	i = 0;
// 	new_eof = ft_eof(eof);
// 	if (ft_strncmp(str, eof, ft_strlen(eof)) == 0)
// 	{
// 		if (str[ft_strlen(eof)] == '\n')
// 		{
// 			free(new_eof);
// 			return (1);
// 		}
// 	}
// 	while (str[i])
// 	{
// 		if (ft_strncmp(&str[i], new_eof, ft_strlen(new_eof)) == 0)
// 		{
// 			free(new_eof);
// 			return (1);
// 		}
// 		i++;
// 	}
// 	free(new_eof);
// 	return (0);
// }

// void	set_readline_pronpt2(t_status *status, char **line)
// {
// 	char	*pronpt;

// 	pronpt = pronpt_ps2(status->envm);
// 	*line = readline(pronpt);
// 	free(pronpt);
// }

// void	set_ans(char *line, size_t *len, char *ans)
// {
// 	(*len) += s_strlen(line);
// 	ans[*len] = '\n';
// 	ans[(*len) + 1] = '\0';
// 	(*len)++;
// 	free(line);
// }

// char	*pipex_gnl_rd(char *eof, t_status *status)
// {
// 	char	*ans;
// 	size_t	len;
// 	char	*line;
// 	char	*pre_ans;

// 	len = 0;
// 	pre_ans = NULL;
// 	line = NULL;
// 	ans = NULL;
// 	rl_catch_signals = 1;
// 	is_here_doc(1);
// 	while (1)
// 	{
// 		if(g_sig == SIGINT)
// 		{
// 			free(line);
// 			free(ans);
// 			ans = NULL;
// 			g_sig = 0;
// 			break;
// 		}
// 		set_readline_pronpt2(status, &line);
// 		ans = (char *)ft_calloc(sizeof(char), len + s_strlen(line) + 2);
// 		if (!ans)
// 			return (free(line), NULL);
// 		if (pre_ans)
// 			ft_strlcpy(ans, pre_ans, s_strlen(pre_ans) + 1);
// 		if(line)
// 			ft_strlcpy(ans + len, line, s_strlen(line) + 1);
// 		pre_ans = ans;
// 		set_ans(line, &len, ans);
// 		if (checker(ans, eof) != 0)
// 			break ;
// 		if(!line)
// 			break;
// 	}
// 	if(ans)
// 		ans[len - ft_strlen(eof)] = '\0';
// 	is_here_doc(0);
// 	return (ans);
// }
