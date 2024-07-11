/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:21 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/11 16:29:16 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_nord(t_info *lst)
{
	t_cmd	*ans;

	ans = (t_cmd *)malloc(sizeof(t_cmd));
	if (ans == NULL)
		error_exit("create_nord");
	ans -> cmd = NULL;
	ans -> path = NULL;
	ans -> arg = (char **)malloc(sizeof(char *));
	ans -> arg[0] = NULL;
	ans -> pipe_0 = 0;
	ans -> pipe_1 = 1;
	ans -> error_file = NULL;
	if (lst -> errstr)
		ans -> error_str = ft_strdup(lst -> errstr);
	else
		ans -> error_str = NULL;
	ans -> next = NULL;
	return (ans);
}

char	**set_cmd(char *str)
{
	char	**ans;

	ans = (char **)malloc(sizeof(char *) * 2);
	if (ans == NULL)
		error_exit("set_cmd");
	ans[0] = ft_strdup(str);
	if (ans[0] == NULL)
		error_exit("set_cmd");
	ans[1] = NULL;
	return (ans);
}

char	**set_args(char *str, char **args)
{
	int		i;
	char	**ans;

	i = 0;
	if (args[i] == NULL)
		return (set_cmd(str));
	while (args[i])
		i++;
	ans = (char **)malloc(sizeof(char *) * (i + 2));
	if (ans == NULL)
		error_exit("set_args");
	i = 0;
	while (args[i])
	{
		ans[i] = ft_strdup(args[i]);
		if (ans[i] == NULL)
			error_exit("set_args");
		i++;
	}
	ans[i] = ft_strdup(str);
	if (ans[i] == NULL)
		error_exit("set_args");
	ans[i + 1] = NULL;
	ft_free(args);
	return (ans);
}

t_cmd	*insert_info(t_info *first, t_cmd *ans)
{
	t_cmd	*cmd_lst;
	t_info	*lst;

	cmd_lst = ans;
	lst = first;
	while (lst)
	{
		// cmd_lst -> error_str = ft_strdup(lst -> errstr);
		if (lst -> type == CMD)
		{
			cmd_lst -> cmd = ft_strdup(lst -> str);
			if (cmd_lst -> cmd == NULL)
				error_exit("insert_info");
			cmd_lst -> arg = set_args(lst -> str, cmd_lst -> arg);
		}
		else if (lst -> type == OPT)
			cmd_lst -> arg = set_args(lst -> str, cmd_lst -> arg);
		else if (lst -> type == PIPE)
			cmd_lst = cmd_lst -> next;
		lst = lst -> next;
	}
	return (ans);
}

t_cmd	*create_lst(t_info *first)
{
	t_cmd	*ans;
	t_cmd	*nord;
	t_info	*lst;
	int		i;

	i = 0;
	ans = create_nord(first);
	nord = ans;
	lst = first;
	i = count_pipe(lst);
	while (i > 0)
	{
		nord -> next = create_nord(first);
		nord = nord -> next;
		i--;
	}
	lst = first;
	ans = insert_info(lst, ans);
	lst = first;
	return (ans);
}
