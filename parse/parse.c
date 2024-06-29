/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:28:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/27 03:28:45 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void prf(void *t)
{
	t_token *token;

	token = (t_token *) t;
	printf("str: %s \t\t| type:%d\n", token->str, token->type);
}

void parse(char *str)
{
	int i;
	t_list *token_list;
	t_token *token;
	int size;

	i = 0;
	token_list = NULL;
	while (str[i])
	{
		while (str[i] && (str[i] == '\t' || str[i] == ' ' || str[i] == '\n'))
			i++;
		size = get_token_size(&str[i]);
		token = new_token(&str[i], size);
		ft_lstadd_back(&token_list, ft_lstnew(token));
		i += size;
	}
	if (check_quote(str, i))
		puterr("quote must be pair");
	ft_lstiter(token_list, prf);
}
