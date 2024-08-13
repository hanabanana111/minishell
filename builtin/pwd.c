/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:53:24 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/14 00:04:44 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pwd_init(t_status *status)
{
	char	*pwd_tmp;

	pwd_tmp = get_value(status->envm, "PWD");
	if (!pwd_tmp || pwd_tmp[0] == '\0')
		return (FALSE);
	status->pwd = pwd_tmp;
	return (TRUE);
}

int	find_pwd_get_pwd(void)
{
	char	*value;

	value = (char *)ft_calloc(1024, sizeof(char));
	if (!value)
		return (FALSE);
	if (!getcwd(value, sizeof(char) * 1024))
		return (FALSE);
	printf("%s\n", value);
	free(value);
	return (TRUE);
}

int	find_pwd_status(t_status *status)
{
	char	*value;

	value = status->pwd;
	if (!value || value[0] == '\0')
		return (FALSE);
	printf("%s\n", value);
	free(value);
	return (TRUE);
}

int	pwd_func(t_status *status)
{
	if (find_pwd_get_pwd())
		return (TRUE);
	if (find_pwd_status(status))
		return (TRUE);
	return (FALSE);
}
