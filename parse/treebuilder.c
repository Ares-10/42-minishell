/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxmethod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:07:39 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/03 23:02:03 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tree	*syntax_pipeline(t_list *token_list)
{
	t_tree	*tree;
	t_token token;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		puterr("malloc failed");
	tree->data = NULL;
	tree->type = T_PIPE;
	tree->left = syntax_cmd(token_list);
	while (token_list && ((t_token *)token_list->content)->type != T_PIPE)
		token_list = token_list->next;
	if (token_list && ((t_token *)token_list->content)->type == T_PIPE)
	{
		if (token_list->next == NULL)
			puterr("wrong pipeline input");
		tree->right = syntax_pipeline(token_list->next);
	}
	else
		tree->right = NULL;
	return (tree);
}

t_tree	*syntax_cmd(t_list *token_list)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		puterr("malloc failed");
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

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		puterr("malloc failed");
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

/*
 * token_list는 pipe, redirect, null 중 하나
 * token_list의 첫 번째 token은 type
 * token_list의 두 번째 token은 file_path
 * 세 번째 인자부터 처리 x
 */
t_tree	*syntax_io_redirect(t_list *token_list)
{
	t_tree		*tree;
	t_redirect	*redirect;
	t_token		*token;

	if (token_list == NULL || ((t_token *)token_list->content)->type != T_REDIRECT)
		return (NULL);
	if (token_list->next == NULL || ((t_token *)token_list->next->content)->type != T_WORD)
		puterr("wrong redirect input");
	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		puterr("malloc failed");
	token = (t_token *)token_list->content;
	if (ft_strncmp(token->str, ">", 1) == 0)
		redirect->type = OUTPUT_REDIRECT;
	else if (ft_strncmp(token->str, ">>", 1) == 0)
		redirect->type = APPEND_REDIRECT;
	else if (ft_strncmp(token->str, "<", 1) == 0)
		redirect->type = INPUT_REDIRECT;
	else if (ft_strncmp(token->str, "<<", 1) == 0)
		redirect->type = HERE_DOCUMENT;
	else
		puterr("wrong redirect input");
	token = (t_token *)token_list->next->content;
	redirect->file_path = ft_strdup(token->str);
	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		puterr("malloc failed");
	tree->type = T_REDIRECT;
	tree->left = NULL;
	tree->right = NULL;
	tree->data = redirect;
	return (tree);
}

/*
 * token_list는 pipe, redirect, null 중 하나
 * token_list의 첫 번째 token은 type
 * token_list의 첫 번째 token 이후는 argv
 */
t_tree	*syntax_simple_cmd(t_list *token_list)
{
	t_tree		*tree;
	t_simplecmd	*cmd;
	t_token		*token;
	char		*tmp;

	if (token_list == NULL || ((t_token *)token_list->content)->type != T_WORD)
		puterr("wrong cmd input");
	cmd = (t_simplecmd *)malloc(sizeof(t_simplecmd));
	if (cmd == NULL)
		puterr("malloc failed");
	token = (t_token *)token_list->content;
	cmd->file_path = ft_strdup(token->str);
	cmd->argv = ft_strdup("");
	while (token_list && ((t_token *)token_list->content)->type == T_WORD)
	{
		token = (t_token *)token_list->content;
		tmp = cmd->argv;
		cmd->argv = ft_strjoin(ft_strjoin(cmd->argv, " "), token->str);
		free(tmp);
		token_list = token_list->next;
	}
	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		puterr("malloc failed");
	tree->type = T_SIMPLECMD;
	tree->left = NULL;
	tree->right = NULL;
	tree->data = cmd;
	return (tree);
}
