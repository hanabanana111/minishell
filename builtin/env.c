/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:53:44 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/11 19:10:14 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_s1(char **env)
{
	int		i;
	char	*str;
	int		l;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "S1=", 3))
		i++;
	if (env[i] == NULL)
		write(2, "minishell: ", 11);
	else
	{
		str = (char *)malloc(ft_strlen(env[i] - 2));
		if (str == NULL)
			error_exit("print_s1");
		l = 3;
		while (env[i][l])
		{
			str[l - 3] = env[i][l];
			l++;
		}
		str[l - 3] = '\0';
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
		free(str);
	}
}

int	check_env_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (1);
	}
	perror_s1(env);
	write(2, "env: No such file or directory\n", 31);
	return (0);
}

int	env_func(t_status *status, t_cmd *lst)
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
		printf("%s\n", status->envm[i++]);
	return (1);
}
