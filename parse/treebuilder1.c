/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxmethod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:07:39 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/08 18:24:53 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tree	*syntax_pipeline(t_list *token_list)
{
	t_tree	*tree;

	tree = (t_tree *)xmalloc(sizeof(t_tree));
	tree->data = NULL;
	tree->type = T_PIPE;
	tree->left = syntax_cmd(token_list);
	while (token_list && ((t_token *)token_list->content)->type != T_PIPE)
		token_list = token_list->next;
	if (token_list && ((t_token *)token_list->content)->type == T_PIPE)
	{
		if (token_list->next == NULL)
			puterr_exit("wrong pipeline input");
		tree->right = syntax_pipeline(token_list->next);
	}
	else
		tree->right = NULL;
	return (tree);
}

t_tree	*syntax_cmd(t_list *token_list)
{
	t_tree	*tree;

	tree = (t_tree *)xmalloc(sizeof(t_tree));
	tree->data = NULL;
	tree->type = T_CMD;
	tree->right = syntax_simple_cmd(token_list);
	while (token_list && ((t_token *)token_list->content)->type == T_WORD)
		token_list = token_list->next;
	tree->left = syntax_redirects(token_list);
	return (tree);
}

/*
 * token_list는 pipe, redirect, null 중 하나
 */
t_tree	*syntax_redirects(t_list *token_list)
{
	t_tree	*tree;

	tree = (t_tree *)xmalloc(sizeof(t_tree));
	tree->data = NULL;
	tree->type = T_REDIRECTS;
	tree->left = syntax_io_redirect(token_list);
	if (token_list)
		token_list = token_list->next;
	while (token_list && ((t_token *)token_list->content)->type == T_WORD)
		token_list = token_list->next;
	if (token_list && ((t_token *)token_list->content)->type == T_REDIRECT)
		tree->right = syntax_redirects(token_list);
	else
		tree->right = NULL;
	return (tree);
}
