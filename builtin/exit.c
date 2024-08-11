/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:27:37 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/11 18:04:27 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_es_digits(t_cmd *lst, int *is_minus)
{
	size_t	i;

	i = 0;
	printf("pass1\n");
	if (!lst->arg[1])
		return (TRUE);
	printf("pass2\n");
	while (ft_isspace_tab_space(lst->arg[1][i]))
		i++;
	printf("pass3\n");
	if (lst->arg[1][i] == '-' || lst->arg[1][i] == '+')
	{
		if (lst->arg[1][i] == '-')
			*is_minus = 1;
		i++;
	}
	printf("pass4\n");
	while (lst->arg[1][i])
	{
		printf("lst->arg[1][i]=[%c]\n",lst->arg[1][i]);
		if (!ft_isdigit(lst->arg[1][i]) && !is_space_till_end(&lst->arg[1][i]))
			return (FALSE);
		i++;
	}
	printf("pass5\n");
	return (TRUE);
}

int	write_error_invalid_argment(char *cmd)
{
	ft_printf(2,"minishell : exit: %s: numeric argument required\n",cmd);
	return (2);
}

int	is_pipe(t_cmd *lst)
{
	if (lst->pre || lst->next)
		return (TRUE);
	return (FALSE);
}

static int	is_oflow(const char *str, int is_minus)
{
	unsigned long	res;
	unsigned long	ul_max;
	unsigned long	num;

	res = 0;
	num = 0;
	if (!str)
		return (FALSE);
	ul_max = (unsigned long)LONG_MAX;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		is_minus = (*str++ == '-');
	while (*str && ft_isdigit(*str))
	{
		num = *str - '0';
		if (!is_minus && res > ul_max / 10)
			return (TRUE);
		else if (!is_minus && res == ul_max / 10 && num > ul_max % 10)
			return (TRUE);
		else if (is_minus && res > ul_max / 10)
			return (TRUE);
		else if (is_minus && res == ul_max / 10 && num > (ul_max + 1) % 10)
			return (TRUE);
		res = res * 10 + *str++ - '0';
	}
	return (FALSE);
}

int	exit_func(t_cmd *lst, int is_parents)
{
	long	end_status;
	int		is_minus;

	end_status = 0;
	is_minus = 0;
	if (!is_pipe(lst) && is_parents)
		printf("exit\n");
	if (!lst->arg[1])
		end_status = 0;
	if (!is_es_digits(lst, &is_minus) || is_oflow(lst->arg[1], is_minus))
		end_status = write_error_invalid_argment(lst->arg[1]);
	else if (lst->arg[1] && lst->arg[2])
		end_status = write_error_str(": exit: too many arguments\n");
	else if (lst->arg[1] && is_es_digits(lst, &is_minus)
		&& !is_oflow(lst->arg[1], is_minus) && !lst->arg[2])
		end_status = (unsigned char)ft_atol(lst->arg[1]);
	if (!is_digits_all(lst))
		return (end_status_func(1),1);
	if (is_parents && !is_pipe(lst))
		exit(end_status);
	if (!is_parents)
		exit(end_status);
	return (0);
}
