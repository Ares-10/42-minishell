/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:28:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 09:13:10 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* 테스트용입니다. */
void	prf(void *t)
{
	t_token	*token;

	token = (t_token *) t;
	printf("str: %s \t\t| type:%d\n", token->str, token->type);
}

void	parse(char *str)
{
	t_list	*token_list;

	tokenize(&token_list, str);
	ft_lstiter(token_list, prf);
	ft_lstclear(&token_list, delete_token);
}
