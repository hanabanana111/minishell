/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:08:51 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/22 21:24:19 by kawaharadar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwddup(void)
{
	char	*ans;
	char	tmp[PATH_MAX];
	int		i;

	if (getcwd(tmp, sizeof(tmp)) < 0)
		error_exit("ft_pwddup");
	i = 0;
	while (tmp[i])
		i++;
	ans = (char *)malloc(i + 1);
	if (ans == NULL)
		error_exit("ft_pwddup");
	i = -1;
	while (tmp[++i])
		ans[i] = tmp[i];
	ans[i] = '\0';
	return (ans);
}

char	*re_pwd(t_status *status, char *str)
{
	char	*ans;
	int		i;
	int		index;

	i = 0;
	index = -1;
	while (status -> pwd[i])
	{
		if (status -> pwd[i] == '/')
			index = i;
		i++;
	}
	if (index == -1)
		error_exit("dont do that!!");
	ans = (char *)malloc(index + 1);
	if (ans == NULL)
		error_exit("re_pwd");
	i = -1;
	while (++i < index)
		ans[i] = status -> pwd[i];
	ans[i] = '\0';
	free(str);
	return (ans);
}
