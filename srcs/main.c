/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:16:41 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/13 10:35:43 by rkawahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }

void	free_t_status(t_status *status)
{
	ft_free_2d_array(status->exp);
	free(status->pwd);
	free(status->home);
	free(status->line);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env[i++]);
	free(env);
}

char	**change_under_bar(char	**env)
{
	int		i;
	char	**ans;

	i = ft_len(env);
	ans = (char **)malloc(sizeof(char *) * (i + 1));
	if (ans == NULL)
		error_exit("change_under_bar");
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "_=", 2))
			ans[i] = ft_strdup(env[i]);
		else
			ans[i] = ft_strdup("_=/usr/bin/env");
		if (ans[i] == NULL)
			error_exit("change_under_bar");
	}
	env[i] == NULL;
	free_env(env);
	return (ans);
}

int	main(int argc, char *argv[], char **env)
{
	t_status	status;

	if (argc > 1)
		return (0);
	(void)argv;
	end_status_func(0);
	ft_bzero(&status, sizeof(t_status));
	status.envm = treat_env(env);
	status.envm = change_under_bar(status.envm);
	if (!set_pwd_init(&status))
		exit(end_status_func(-1));
	if (!set_home(&status))
		exit(end_status_func(-1));
	status.exp = create_export(status.envm);
	treat_signal();
	treat_read(&status);
	free_t_status(&status);
	exit(end_status_func(-1));
}
