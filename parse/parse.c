/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:28:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/07 21:48:50 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* 테스트용입니다 */
void	prf(void *t)
{
	t_token	*token;
	int		type;

	token = (t_token *) t;
	printf("str: %s \t\t| type: ", token->str);
	type = token->type;
	if (type == T_PIPE)
		printf("T_PIPE\n");
	else if (type == T_WORD)
		printf("T_WORD\n");
	else if (type == T_REDIRECT)
		printf("T_REDIRECT\n");
	else
		puterr("type failed");
}

/*
 * 테스트용입니다
 * 전위순회순으로 트리를 출력합니다
 */
void	search_tree(t_tree *tree)
{
	int			type;
	t_simplecmd	*cmd;
	t_redirect	*redirect;

	type = tree->type;
	if (type == T_PIPE)
		printf("T_PIPE\n");
	else if (type == T_CMD)
		printf("T_CMD\n");
	else if (type == T_REDIRECTS)
		printf("T_REDIRECTS\n");
	else if (type == T_SIMPLECMD)
	{
		printf("T_SIMPLECMD\t| ");
		cmd = (t_simplecmd *)tree->data;
		printf("file_path: %s | argv: %s\n", cmd->file_path, cmd->argv);
	}
	else if (type == T_REDIRECT)
	{
		printf("T_REDIRECT\t| ");
		redirect = (t_redirect *)tree->data;
		if (redirect->type == OUTPUT_REDIRECT)
			printf("type: > | file_path: %s\n", redirect->file_path);
		else if (redirect->type == INPUT_REDIRECT)
			printf("type: < | file_path: %s\n", redirect->file_path);
		else if (redirect->type == APPEND_REDIRECT)
			printf("type: >> | file_path: %s\n", redirect->file_path);
		else if (redirect->type == HERE_DOCUMENT)
			printf("type: << | file_path: %s\n", redirect->file_path);
	}
	else
		puterr("type failed");
	if (tree->left != NULL)
		search_tree(tree->left);
	if (tree->right != NULL)
		search_tree(tree->right);
}

void	*parse_err(char *msg)
{
	ft_putstr_fd("parse error: ", 2);
	ft_putendl_fd(msg, 2);
	return (FAILURE);
}

t_tree	*parse(char *str)
{
	t_list	*token_list;
	t_tree	*parse_tree;
	char	*new_str;

	new_str = replace_variable(str);
	if (new_str == FAILURE)
		parse_err("bad var name");
	tokenize(&token_list, str);
	// ft_lstiter(token_list, prf); // 테스트용
	parse_tree = syntax_pipeline(token_list);
	// search_tree(parse_tree); // 테스트용
	ft_lstclear(&token_list, delete_token);
	return (parse_tree);
}
