/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:27:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/15 16:54:17 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ans_checker(char *ans)
{
	size_t	i;

	i = 0;
	while (ans[i])
	{
		if (ans[i] != '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*s_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, " ", 2);
	ft_strlcpy(result + s1_len + 1, s2, s2_len + 1);
	return (result);
}

int	here_doc_pipe(t_info *cmd_info, t_status *status)
{
	t_info	*node;

	node = cmd_info;
	if (status->is_pipe_syntax || status->is_redi_syntax)
		return (FALSE);
	while (node->next)
		node = node->next;
	if (node->type == PIPE && !node->next)
	{
		ft_printf(1, "Invalid end with pipe\n");
		return (TRUE);
	}
	else
		return (FALSE);
}
