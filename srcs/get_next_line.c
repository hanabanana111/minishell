/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:41:49 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/20 17:19:15 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_getchar(int fd, t_buf *gnl)
{
	if (gnl->n == 0)
	{
		gnl->n = read(fd, gnl->buf, 42);
		if (gnl->n < 0)
		{
			ft_bzero(gnl, sizeof(t_gnl));
			return (-2);
		}
		gnl->bufp = gnl->buf;
	}
	if (--gnl->n >= 0)
		return ((unsigned char)*gnl->bufp++);
	else
	{
		ft_bzero(gnl, sizeof(t_gnl));
		return (EOF);
	}
}

char	*get_next_line(int fd, t_buf *bufs)
{
	char	*first;
	char	*result;
	char	str[2];
	char	c;

	result = NULL;
	first = NULL;
	ft_bzero(&str, sizeof(str));
	while (fd >= 0)
	{
		first = result;
		c = ft_getchar(fd, bufs);
		if (c == EOF && !result)
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
