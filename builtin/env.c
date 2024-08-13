/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:53:44 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/14 00:46:54 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
	}
	ft_printf(2, "minishell: env: No such file or directory\n");
	end_status_func(127);
	return (0);
}

void	printf_shlvl(char *shlvl, t_cmd *lst)
{
	char	*tmp;
	int		i;
	int		l;
	char	*tmp2;

	if (ft_lstlen(lst) > 1)
	{
		tmp = (char *)malloc(ft_strlen(shlvl) - 5);
		i = 5;
		while (shlvl[++i])
			tmp[i - 6] = shlvl[i];
		tmp[i - 6] = '\0';
		l = ft_atoi(tmp);
		if (l > 0)
			l--;
		free(tmp);
		tmp = ft_itoa(l);
		tmp2 = ft_strjoin("SHLVL=", tmp);
		printf("%s\n", tmp2);
		free(tmp);
		free(tmp2);
	}
	else
		printf("%s\n", shlvl);
}

int	env_func(t_status *status, t_cmd *lst)
{
	size_t	i;

	i = 0;
	if (check_env_path(status->envm) == 0)
		return (1);
	// if (lst->pre || lst->next)
	// 	return (0);
	if (!status->envm || !status->envm[i])
	{
		printf("\n");
		return (0);
	}
	while (status->envm[i])
	{
		if (strncmp(status->envm[i], "SHLVL=", 6) == 0)
			printf_shlvl(status->envm[i], lst);
		else
			printf("%s\n", status->envm[i]);
		i++;
	}
	return (1);
}

int	env_func2(t_status *status, t_cmd *lst)
{
	size_t	i;

	i = 0;
	if (check_env_path(status->envm) == 0)
		return (1);
	if (lst->pre || lst->next)
		return (0);
	if (!status->envm || !status->envm[i])
	{
		printf("\n");
		return (0);
	}
	while (status->envm[i])
	{
		if (strncmp(status->envm[i], "SHLVL=", 6) == 0)
			printf_shlvl(status->envm[i], lst);
		else
			printf("%s\n", status->envm[i]);
		i++;
	}
	return (1);
}