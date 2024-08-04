/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:25:17 by kawaharadar       #+#    #+#             */
/*   Updated: 2024/08/04 22:18:37 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_index(char *str, char c)
{
	int		i;
	char	*ans;

	i = 0;
	while (str[i] != c)
		i++;
	ans = (char *)malloc(i+1);
	if (ans == NULL)
		error_exit("ft_strdup_index");
	i = 0;
	while (str[i] != c)
	{
		ans[i] = str[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	**eq_exp(char **exp, char *str)
{
	char	*tmp;

	tmp = ft_strdup_index(str, '=');
	if (check_exp(exp, tmp) >= 0)
		exp = remove_exp(exp, tmp);
	exp = add_export(exp, str);
	free(tmp);
	return (exp);
}

char	*ft_strjoin4(char *s1, char *s2, char c)
{
	int		len1;
	int		len2;
	int		index;
	int		i;
	char	*ans;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	index = 0;
	while (s2[index] != c)
		index++;
	ans = (char *)malloc(len1 + len2 - index + 1);
	if (ans == NULL)
		error_exit("ft_strjoin4");
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	while (s2[index])
		ans[i++] = s2[index++];
	ans[i] = '\0';
	free(s1);
	return (ans);
}

char	*ft_expjoin(char *tmp, char *str)
{
	int		index;
	char	*ans;

	index = 0;
	while (str[index] != '=')
		index++;
	ans = malloc(ft_strlen(tmp) + ft_strlen(str) - index - 1);
	if (ans == NULL)
		error_exit("ft_expjoin");
	ft_expjoin2(tmp, ans, index, str);
	free(tmp);
	return (ans);
}

char	**plus_eq_exp(char **exp, char *str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup_index(str, '+');
	if (check_exp(exp, tmp) < 0)
	{
		tmp = ft_strjoin4(tmp, str, '=');
		exp = add_export(exp, tmp);
		free(tmp);
		return (exp);
	}
	else
	{
		tmp2 = ft_strdup(exp[check_exp(exp, tmp)]);
		tmp2 = ft_strtrim2(tmp2, 11);
		if (check_eq2(tmp2))
			tmp2 = ft_expjoin(tmp2, str);
		else
			tmp2 = ft_expstr(str, tmp2);
		exp = remove_exp(exp, tmp);
		exp = add_export(exp, tmp2);
		free(tmp);
		free(tmp2);
		return (exp);
	}
}

int	export_func2(char **arg, t_status *status, t_cmd *first)
{
	(void)first;
	if (ft_len(arg) == 1)
		print_export(status->exp);
	return (1);
}
