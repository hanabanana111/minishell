/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:12:20 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/22 20:11:08 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_s1(char **env)
{
	int		i;
	char	*str;
	int		l;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "S1=", 3))
		i++;
	if (env[i] == NULL)
		printf("minishell: ");
	else
	{
		str = (char *)malloc(ft_strlen(env[i] - 2));
		if (str == NULL)
			error_exit("print_s1");
		l = 3;
		while (env[i][l])
		{
			str[l - 3] = env[i][l];
			l++;
		}
		str[l - 3] = '\0';
		printf("%s: ", str);
		free(str);
	}
}

void	free_cmd(t_cmd *lst)
{
	int		i;
	t_cmd	*tmp;

	while (lst)
	{
		free(lst -> cmd);
		free(lst -> path);
		i = 0;
		while (lst -> arg[i])
			free(lst -> arg[i++]);
		free(lst -> flg);
		free(lst -> arg[i]);
		free(lst -> arg);
		if (lst -> pipe_0 > 1)
			close(lst -> pipe_0);
		if (lst -> pipe_1 > 1)
			close(lst -> pipe_1);
		free(lst -> error_file);
		free(lst -> error_str);
		tmp = lst;
		lst = lst -> next;
		free(tmp);
	}
}

void	re_free(char *str, t_info *lst)
{
	t_info	*tmp;
	t_info	*node;

	(void)str;
	node = lst;
	str = NULL;
	while (node)
	{
		tmp = node;
		free(node->str);
		free(node->key);
		free(node->errstr);
		node = node->next;
		free(tmp);
	}
}
