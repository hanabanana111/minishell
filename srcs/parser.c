/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:24:40 by hakobori          #+#    #+#             */
/*   Updated: 2024/07/08 04:55:27 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_syntax_error(char *str,t_info *node)
{
    char *head;
    
    if(node->flg)
        head = node->errstr;
    else
        head =ft_strdup("minishell");
    printf("%s: syntax error near unexpected token `%s'", head,str);
    if(!node->flg)
        free(head);
}

void is_syntax_is_heredoc(t_syn_here *syn_here,t_info *cmd_info)
{
    t_info	*node;
    
    node = cmd_info;
	while (node)
	{
        // if()
		if(ft_strnstr(node->str,">>>",s_strlen(node->str)))
        {
            syn_here->is_syntax = 1;
            //show_syntax_error(">",node);
        }
        else if(ft_strnstr(node->str,"|||",s_strlen(node->str)))
        {
            syn_here->is_syntax = 2;
            //show_syntax_error("|",node);
        }
        else if(ft_strnstr(node->str,"<<",s_strlen(node->str)) && node->next)
        {
            
        }
		node = node->next;
        if(ft_strnstr(node->str,"|",s_strlen(node->str)))
            break;
	}
}

void	parser(t_info *cmd_info, t_status *status)
{
	// t_info	*node;
    t_syn_here syn_here;
    
	//to_parse_lst(&cmd_info);
    ft_bzero(&syn_here,sizeof(t_syn_here));
    //is_syntax_is_heredoc(syn_here,cmd_info);
    (void)status;
	// node = cmd_info;
	// while (node)
	// {
	// 	printf("cmd = %s\n", node->str);
    //     printf("type = %d\n", node->type);
    //     if(node->pre)
    //         printf("node->pre = %p\n", node->pre);
	// 	node = node->next;
	// }
    (void)cmd_info;
    // debug_print_lst(cmd_info);
}

void debug_print_lst(t_info *cmd_info)
{
    t_info	*node;
    
	node = cmd_info;
	while (node)
	{
		printf("cmd = %s\n", node->str);
        printf("type = %d\n", node->type);
        if(node->pre)
            printf("node->pre = %p\n", node->pre);
        if(node->is_quote)
            printf("node->is_quote = %d \
            \n", node->is_quote);
		node = node->next;
	}
}