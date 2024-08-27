/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:41:49 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/27 18:56:06 by hakobori         ###   ########.fr       */
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
			ft_bzero(gnl, sizeof(t_buf));
			return (-2);
		}
		gnl->bufp = gnl->buf;
	}
	if (--gnl->n >= 0)
		return ((unsigned char)*gnl->bufp++);
	else
	{
		ft_bzero(gnl, sizeof(t_buf));
		return (EOF);
	}
}

void	gnl_init(char **result, char **first)
{
	*result = NULL;
	*first = NULL;
}

char	*get_next_line(int fd, t_buf *bufs)
{
	char	*first;
	char	*result;
	char	str[2];
	char	c;

	ft_bzero(&str, sizeof(str));
	gnl_init(&result, &first);
	while (fd >= 0)
	{
		first = result;
		c = ft_getchar(fd, bufs);
		if (c == EOF && !result)
			break ;
		if (c == -2)
			return (free(result), NULL);
		str[0] = c;
		if (c == EOF)
			str[0] = '\0';
		result = ft_strjoin(result, str);
		free(first);
		if (c == '\n')
			break ;
	}
	return (result);
}
