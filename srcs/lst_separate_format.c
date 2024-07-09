/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_separate_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:16:23 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/09 20:19:38 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(char const *s, size_t n)
{
	size_t	i;
	char	*result;

	result = (char *)ft_calloc(n + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		result[i] = s[i];
		i++;
	}
	return (result);
}

int check_cmd(char *cmd, char *str)
{
    char    cmd_c;
    int     i;

    i = 0;
    cmd_c = cmd[0];
    while (str[i])
    {
        if (str[i] != cmd_c || i == 2)
            return (FALSE);
        i++;
    }
    return (TRUE);
}

void separate_cmd(char *cmd,t_info *node,size_t *j)
{
    char *pre_str;
    t_info *pre_node;
    t_info *next_node;
    int i;
    size_t cmd_len;
    
    i = 0;
    cmd_len = s_strlen(cmd);
    while(node->str[i])
    {
        if(i == 0 && node->str[cmd_len] && !ft_strncmp(node->str,cmd,cmd_len))
        {
            if(check_cmd(cmd, node -> str))
                break;
            //printf("1:Splitting at start: %s\n", node->str);
            pre_str = node->str;
            pre_node = node;
            next_node = node->next;
            node->str =ft_strndup(pre_str,cmd_len);
            node->next = info_lstnew(&pre_str[cmd_len]);
            node->next->pre = pre_node;
            node->next->next = next_node;
            free(pre_str);
            (*j) = (*j) + cmd_len - 1;
            break;
        }
        else if(i != 0 &&!ft_strncmp(&node->str[i],cmd,cmd_len))
        {
            //printf("2:Splitting at start: %s\n", node->str);
            // if(cmd[0] == node->str[i])
            //     break;
            pre_str = node->str;
            pre_node = node;
            next_node = node->next;
            node -> str = ft_strndup(pre_str,i);
            //printf("node -> next -> str = %s\n", &pre_str[i]);
            node->next = info_lstnew(&pre_str[i]);
            node->next->pre = pre_node;
            node->next->next = next_node;
            free(pre_str);
            break;
        }
        i++;
    }
}

void find_separater(t_info *node)
{
    size_t i;

    i = 0;
    while(node->str[i])
    {
        // if(!ft_strncmp(&node->str[i],"|||",3))
        //     separate_cmd("|||",node,&i);
        if(!ft_strncmp(&node->str[i],"||",2))
            separate_cmd("||",node,&i);
        else if(!ft_strncmp(&node->str[i],"|",1))
            separate_cmd("|",node,&i);
        // else if(!ft_strncmp(&node->str[i],"<<<",3))
        //     separate_cmd("<<<",node,&i);
        else if(!ft_strncmp(&node->str[i],"<<",2))
            separate_cmd("<<",node,&i);
        else if(!ft_strncmp(&node->str[i],"<",1))
            separate_cmd("<",node,&i);
        // else if(!ft_strncmp(&node->str[i],">>>",3))
        //     separate_cmd(">>>",node,&i);
        else if(!ft_strncmp(&node->str[i],">>",2))
            separate_cmd(">>",node,&i);
        else if(!ft_strncmp(&node->str[i],">",1))
            separate_cmd(">",node,&i);
        i++;
    }
}

void separator(t_info *cmd_info)
{
    t_info *node;

    node = cmd_info;
    while(node)
    {
        //printf("node -> str = %s\n", node -> str);
        if(node->str && !node->is_quote)
            find_separater(node);
        node = node->next;
    }
}