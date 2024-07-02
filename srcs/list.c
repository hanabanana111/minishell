/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:13:50 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/02 16:28:23 by rkawahar         ###   ########.fr       */
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
	ans -> pipe_0 = NULL;
	ans -> pipe_1 = NULL;
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
	ans = (char **)malloc(sizeof(char *) * (i + 1));
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

void	insert_info(t_info *lst, t_cmd *cmd_lst)
{
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
}

t_cmd	*create_lst(t_info *lst)
{
	t_cmd	*ans;
	t_cmd	*tmp;
	int		i;

	i = 0;
	ans = create_nord();
	i = count_pipe(lst);
	while (i > 0)
	{
		tmp = create_nord();
		ft_lastlst(ans)-> next = tmp;
		i--;
	}
	insert_info(lst, ans);
}
