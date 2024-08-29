/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/29 15:45:06 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_es_digits(t_cmd *lst, int *is_minus)
{
	size_t	i;

	i = 0;
	if (lst->arg && lst->arg[0] && !lst->arg[1])
		return (TRUE);
	while (ft_isspace_tab_space(lst->arg[1][i]))
		i++;
	if (lst->arg[1][i] == '-' || lst->arg[1][i] == '+')
	{
		if (lst->arg[1][i] == '-')
			*is_minus = 1;
		i++;
	}
	if (lst->arg[1][i] == '\0')
		return (FALSE);
	while (lst->arg[1][i])
	{
		if (!ft_isdigit(lst->arg[1][i]) && !is_space_till_end(&lst->arg[1][i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_pipe(t_cmd *lst)
{
	if (lst->pre || lst->next)
		return (TRUE);
	return (FALSE);
}

int	is_oflow(const char *str, int minus)
{
	unsigned long	res;
	unsigned long	ul_max;
	unsigned long	num;

	res = 0;
	num = 0;
	ul_max = (unsigned long)LONG_MAX;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		minus = (*str++ == '-');
	while (*str && ft_isdigit(*str))
	{
		num = *str - '0';
		if (!minus && res > ul_max / 10)
			return (TRUE);
		else if (!minus && res == ul_max / 10 && num > ul_max % 10)
			return (TRUE);
		else if (minus && res > ul_max / 10)
			return (TRUE);
		else if (minus && res == ul_max / 10 && num > (ul_max + 1) % 10)
			return (TRUE);
		res = res * 10 + *str++ - '0';
	}
	return (FALSE);
}

int	is_exit_first_arg(t_cmd *lst)
{
	if (lst->arg && lst->arg[0] && lst->arg[1])
		return (TRUE);
	return (FALSE);
}

int	exit_func(t_cmd *lst, int is_parents)
{
	int	is_minus;
	int	is_exit_arg;

	is_minus = 0;
	is_exit_arg = is_exit_first_arg(lst);
	if (!is_pipe(lst) && is_parents)
		printf("exit\n");
	if (!is_exit_arg)
		end_status_func(-1);
	if (is_parents)
		print_numeric_arg(lst);
	if (is_parents && !is_pipe(lst) && !is_exit_arg)
		exit(end_status_func(-1));
	else if (is_exit_arg && lst->arg[2])
	{
		write_error_str(": exit: too many arguments\n");
		return (end_status_func(1), 1);
	}
	else if (is_exit_arg && is_es_digits(lst, &is_minus)
		&& !is_oflow(lst->arg[1], is_minus) && !lst->arg[2])
		end_status_func((unsigned char)ft_atol(lst->arg[1]));
	if ((is_parents && !is_pipe(lst)) || !is_parents)
		exit(end_status_func(-1));
	return (0);
}
