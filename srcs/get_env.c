/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:58 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/13 12:01:14 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_level(char *env)
{
	size_t	i;
	int		tmp;
	char	*a_num;
	char	*ret;

	i = 6;
	tmp = ft_atoi(&env[i]);
	tmp++;
	if (tmp >= 1000)
		tmp = 1;
	if (tmp < 0)
		tmp = 0;
	a_num = ft_itoa(tmp);
	ret = ft_strjoin("SHLVL=", a_num);
	free(a_num);
	return (ret);
}

char	**treat_env(char **env)
{
	char	**ret;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!env || !env[i])
		return (NULL);
	while (env[i])
		if (ft_strncmp("OLDPWD=", env[i++], 7))
			count++;
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
			ret[count++] = shell_level(env[i]);
		else if (ft_strncmp("OLDPWD=", env[i], 7))
			ret[count++] = ft_strdup(env[i]);
		i++;
	}
	return (ret);
}

char	*format_value(char *env, char *key)
{
	char	*ret;
	size_t	value_len;
	size_t	i;

	i = 0;
	while (env[i] == key[i])
		i++;
	if (env[i] == '+')
		i++;
	i++;
	value_len = s_strlen(&env[i]);
	ret = (char *)ft_calloc(value_len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &env[i], s_strlen(&env[i]) + 1);
	return (ret);
}

char	*get_value(char **env, char *key)
{
	size_t	i;
	size_t	key_len;

	i = 0;
	if (!key)
		return (NULL);
	key_len = s_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (format_value(env[i], key));
		i++;
	}
	return ("");
}

char	*key_format(char *str)
{
	size_t	i;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '+')
		i++;
	if (!str[i])
		return (NULL);
	result = (char *)ft_calloc(i + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, i + 1);
	return (result);
}
