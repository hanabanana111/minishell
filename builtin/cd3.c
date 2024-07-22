/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kawaharadaryou <kawaharadaryou@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:08:51 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/07/22 19:16:13 by kawaharadar      ###   ########.fr       */
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
