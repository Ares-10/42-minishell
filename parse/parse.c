/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:28:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/12 21:43:29 by seojepar         ###   ########.fr       */
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
		puterr_exit("type failed");
}

/*
 * 테스트용입니다
 * 전위순회순으로 트리를 출력합니다
 */
void	print_tree(t_tree *tree)
{
	int			type;
	int			i;
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
		printf("file_path: %s | argv: ", cmd->file_path);
		i = -1;
		while (cmd->argv[++i])
			printf("%s, ", cmd->argv[i]);
		printf("%s\n", cmd->argv[i]);
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
		puterr_exit("type failed");
	if (tree->left != NULL)
		print_tree(tree->left);
	if (tree->right != NULL)
		print_tree(tree->right);
}

void	*parse_err(char *msg)
{
	ft_putstr_fd("parse error: ", 2);
	ft_putendl_fd(msg, 2);
	return (FAILURE);
}

t_tree	*parse(char *str, char **envp)
{
	t_list	*token_list;
	t_tree	*parse_tree;
	t_pipe	*info;
	char	*new_str;

	new_str = replace_variable(str, envp);
	if (new_str == FAILURE)
		parse_err("bad $var name");
	tokenize(&token_list, new_str);
	// ft_lstiter(token_list, prf); // 테스트용
	parse_tree = syntax_pipeline(token_list);
	// print_tree(parse_tree); // 테스트용
	ft_lstclear(&token_list, delete_token);
	return (parse_tree);
}
