/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:55:29 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/13 01:59:35 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fce(char *str, int fd, t_cmd *lst);

char	*recreate_minishell(char *str, char tmp)
{
	char	*ans;
	int		i;

	i = 0;
	ans = (char *)malloc(ft_strlen(str) + 2);
	if (ans == NULL)
		error_exit("recreate_minishell");
	while (str && str[i])
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

	ans = NULL;
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
	char	*num;

	num = ft_itoa(line);
	e_str = ft_strdup(file);
	e_str = ft_strjoin2(e_str, ": line ");
	if (e_str == NULL)
		error_exit("create_info_nord");
	e_str = ft_strjoin2(e_str, num);
	free (num);
	if (e_str == NULL)
		error_exit("create_info_nord");
	ans = (t_info *)malloc(sizeof(t_info));
	if (ans == NULL)
		error_exit("create_info_nord");
	ft_bzero(ans, sizeof(t_info));
	ans -> str = lst_str;
	ans -> type = -1;
	ans -> errstr = e_str;
	ans -> flg = 1;
	ans -> e_flg = 1;
	ans -> is_quote = 0;
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
	if (args == NULL)
		error_exit("create_info");
	i = 0;
	ans = create_info_nord(args[i], file, line);
	lst = ans;
	i++;
	while (args[i])
	{
		tmp = create_info_nord(args[i], file, line);
		lst -> next = tmp;
		tmp -> pre = lst;
		lst = lst -> next;
		i++;
	}
	return (ans);
}

void	re_process(t_cmd *lst, t_status *env_lst)
{
	int		i;
	char	*str;
	int		fd;
	t_info	*tmp;

	fd = open(lst -> cmd, R_OK);
	if (fd < 0)
	{
		print_s1(env_lst -> envm);
		if (lst -> error_file)
			printf("%s: ", lst -> error_file);
		perror(lst -> cmd);
	}
	i = 1;
	str = minishell_gnl(fd);
	while (str != NULL)
	{
		tmp = create_info(str, lst -> cmd, i++);
		set_lst_details(&tmp, env_lst -> envm);
		parser(tmp, env_lst);
		ft_miniprocess(tmp, env_lst);
		re_free(str, tmp);
		str = minishell_gnl(fd);
	}
	fce(str, fd, lst);
}
