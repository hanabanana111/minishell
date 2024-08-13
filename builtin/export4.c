/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:30:09 by rkawahar          #+#    #+#             */
/*   Updated: 2024/08/13 23:56:26 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0)
		{
			if (arg[i] != '_' && !ft_isalpha(arg[i]))
				return (0);
		}
		else
		{
			if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
			{
				if (arg[i] != '+' || (arg[i] == '+' && arg[i + 1] != '='))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

void	error_printf(char *arg, t_cmd *lst)
{
	if (lst -> error_str)
		write(2, lst -> error_str, ft_strlen(lst -> error_str));
	else
		write(2, "minishell", 9);
	write(2, ": ", 2);
	write(2, "export: '", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	end_status_func(1);
}

int	check_export_shlvl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
	}
	return (1);
}

void	shlvl_export(char *str, t_status *status)
{
	if (str[5] && str[5] == '=' && str[6] == '\0')
	{
		add_env(status, "SHLVL=0");
		status -> exp = eq_exp(status -> exp, str);
	}
	else if (check_export_shlvl(str))
	{
		if (check_type2(str) == 1)
			return ;
		if (check_type2(str) == 2)
		{
			status -> exp = eq_exp(status -> exp, str);
			add_env(status, str);
		}
		else
		{
			status -> exp = plus_eq_exp(status -> exp, str);
			add_env(status, str);
		}
	}
}
