/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:55:29 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/05 20:19:38 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recreate_minishell(char *str, char tmp)
{
	char	*ans;
	int		i;

	i = 0;
	ans = (char *)malloc(sizeof(str) + 2);
	while (str[i])
	{
		ans[i] = str[i];
		i++;
	}
	ans[i] = tmp;
	ans[i + 1] = '\0';
	free(str);
	return (ans);
}

char	*minishell_gnl(int fd)
{
	char	*ans;
	char	tmp;
	int		read_byte;

	ans = (char)malloc(1);
	ans[0] = '\0';
	tmp = '\0';
	read_byte = 1;
	while (1)
	{
		read_byte = read(fd, &tmp, 1);
		if (read_byte <= 0 || tmp == '\n')
			break ;
		ans = recreate_minishell(ans, tmp);
	}
	if (ft_strlen(ans) == 0 && read_byte <= 0)
		return (NULL);
	return (ans);
}

t_info	*create_info_nord(char *lst_str, char *file, int line)
{
	char	*e_str;
	t_info	*ans;

	e_str = ft_strdup(file);
	e_str = ft_strjoin2(e_str, ": line ");
	e_str = ft_strjoin2(e_str, ft_itoa(line));
	e_str = ft_strjoin2(e_str, ": ");
	ans = (t_info *)malloc(sizeof(t_info));
	ans -> str = lst_str;
	ans -> type = NULL;
	ans -> errstr = e_str;
	ans -> flg = 1;
	ans -> next = NULL;
	return (ans);
}

t_info	*create_info(char *str, char *file, int line)
{
	t_info	*ans;
	t_info	*lst;
	t_info	*tmp;
	int		i;
	char	**args;

	args = ft_split(str, ' ');
	i = 0;
	ans = create_info_nord(args[i], file, line);
	lst = ans;
	i++;
	while (args[i])
	{
		tmp = create_info_nord(args[i], file, line);
		lst -> next = tmp;
		lst = lst -> next;
		i++;
	}
	return (ans);
}

void	re_process(t_cmd *lst, char **env)
{
	int		i;
	char	*str;
	int		fd;

	fd = open(lst -> cmd, R_OK);
	if (fd < 0)
		error_exit(lst -> cmd);
	i = 1;
	str = minishell_gnl(fd);
	while (str != NULL)
	{
		//はなさんの関数に直接ぶち込む
		create_info(str, lst -> cmd, i);
		i++;
		free(str);
		str = minishell_gnl(fd);
	}
	free(str);
	close(fd);
}
