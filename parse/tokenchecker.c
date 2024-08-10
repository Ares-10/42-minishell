/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenchecker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:33:57 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/14 21:34:02 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static int	puterr_int_ret(char *msg)
{
	puterr(msg);
	return (FAILURE);
}

int	token_check(t_list *token_list)
{
	t_token	*token;
	t_token	*prv_token;

	prv_token = NULL;
	while (token_list)
	{
		token = token_list->content;
		if (token->type == T_PIPE)
		{
			if (prv_token == NULL || prv_token->type != T_WORD
				|| token_list->next == NULL
				|| ((t_token *)token_list->next->content)->type == T_PIPE)
				return (puterr_int_ret("wrong pipeline input"));
		}
		else if (token->type == T_REDIRECT)
		{
			if (token_list->next == NULL
				|| ((t_token *)token_list->next->content)->type != T_WORD)
				return (puterr_int_ret("wrong redirect input"));
		}
		prv_token = token_list->content;
		token_list = token_list->next;
	}
	return (SUCCESS);
}
