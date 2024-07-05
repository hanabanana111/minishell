/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:43:21 by rkawahar          #+#    #+#             */
/*   Updated: 2024/07/05 18:06:49 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_nord(void)
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
	ans -> next = NULL;
	return (ans);
}

char	**set_args(char *str, char **args)
{
	int		i;
	char	**ans;

	i = 0;
	if (args == NULL)
	{
		ans = (char **)malloc(sizeof(char *) * 2);
		ans[0] = ft_strdup(str);
		ans[1] = NULL;
		return (ans);
	}
	while (args[i])
		i++;
	ans = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args[i])
	{
		ans[i] = ft_strdup(args[i]);
		i++;
	}
	ans[i] = ft_strdup(str);
	ans[i + 1] = NULL;
	ft_free(args);
	return (ans);
}

t_cmd	*ft_lastlst(t_cmd *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

t_cmd	*insert_info(t_info *lst, t_cmd *cmd_lst)
{
	t_cmd	*ans;

	ans = cmd_lst;
	while (lst)
	{
		if (lst -> type == CMD)
		{
			cmd_lst -> cmd = ft_strdup(lst -> str);
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

t_cmd	*create_lst(t_info *lst)
{
	t_cmd	*ans;
	t_cmd	*nord;
	t_cmd	*tmp;
	int		i;

	i = 0;
	ans = create_nord();
	nord = ans;
	i = count_pipe(lst);
	while (i > 0)
	{
		tmp = create_nord();
		ft_lastlst(nord)-> next = tmp;
		i--;
	}
	ans = insert_info(lst, ans);
	return (ans);
}
