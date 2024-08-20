/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 08:11:50 by hakobori          #+#    #+#             */
/*   Updated: 2024/08/20 08:14:37 by hakobori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quotes_char(char str_char, char *quote_char)
{
	if (!*quote_char)
		*quote_char = str_char;
	else if (*quote_char == str_char)
		*quote_char = 0;
}
