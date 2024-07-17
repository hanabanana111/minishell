/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:37:15 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/17 21:51:54 by kawaharadar      ###   ########.fr       */
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

int	check_type2(char *str)
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

void	ft_mini_export(t_status *status, char *arg)
{
	if (check_type2(arg) == 1)
		status -> exp = no_eq_exp(status -> exp, arg);
	else if (check_type2(arg) == 2)
	{
		status -> exp = eq_exp(status -> exp, arg);
		add_env(status, arg);
	}
	else
	{
		status -> exp = plus_eq_exp(status -> exp, arg);
		add_env(status, arg);
	}
}

int	export_func(char **arg, t_status *status, t_cmd *first)
{
	int	i;

	if (ft_lstlen(first) > 1)
		return (0);
	if (ft_len(arg) == 1)
		print_export(status -> exp);
	else
	{
		i = 1;
		while (arg[i])
		{
			ft_mini_export(status, arg[i]);
			i++;
		}
	}
	return (1);
}
