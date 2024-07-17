/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:37:15 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 17:46:19 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		printf("%s\n", exp[i]);
		i++;
	}
}

int	check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (3);
			return (2);
		}
		i++;
	}
	return (1);
}

char	**no_eq_exp(char **exp, char *str)
{
	if (check_exp(exp, str) >= 0)
		return (exp);
	exp = add_export(exp, str);
	return (exp);
}

void	ft_mini_export(char **exp, char **env, char *arg)
{
	if (check_type(arg) == 1)
		exp = no_eq_exp(exp, arg);
	else if (check_type(arg) == 2)
	{
		exp = eq_exp(exp, arg);
		//はなさんの作ってくれた優秀関数
	}
	else
	{
		exp = plus_eq_exp(exp, arg);
		//はなさんの作った優秀関数
	}
}

int	export_func(char **arg, char **exp, char **env, t_cmd *first)
{
	int	i;

	if (ft_lstlen(first) > 1)
		return (0);
	if (ft_len(arg) == 1)
		print_export(exp);
	else
	{
		i = 1;
		while (arg[i])
		{
			ft_mini_export(exp, env, arg[i]);
			i++;
		}
	}
	return (1);
}
