/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:28:45 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/11 05:50:50 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

/*
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
		else if (redirect->type == HERE_DOC)
			printf("type: << | file_path: %s\n", redirect->file_path);
	}
	else
		puterr_exit("type failed");
	if (tree->left != NULL)
		print_tree(tree->left);
	if (tree->right != NULL)
		print_tree(tree->right);
}
*/

void	*parse_err(char *msg)
{
	ft_putstr_fd("parse error: ", 2);
	ft_putendl_fd(msg, 2);
	return (FAILURE);
}

static int	check_unsupported_str(char *str)
{
	int	i;
	int	flag;
	int	quote_flag;

	quote_flag = 0;
	i = -1;
	while (str[++i])
	{
		flag = check_quote(str, i);
		if (flag == 0 && (str[i] == ';' || str[i] == '\\'))
		{
			puterr("parse: unsupported input");
			return (FAILURE);
		}
		if (flag == -1)
			quote_flag = !quote_flag;
	}
	if (quote_flag == 1)
	{
		puterr("parse: quote must be pair");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	set_exit_status(char *str, char **envp)
{
	int i;
	int	flag;

	flag = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '|' && check_quote(str, i) == 0)
			flag = 1;
	if (flag)
	{
		free(envp[0]);
		envp[0] = ckm(ft_strdup("?=0"));
	}
}

t_tree	*parse(char *str, char **envp)
{
	t_list	*token_list;
	t_tree	*parse_tree;
	char	*new_str;

	set_exit_status(str, envp);
	if (check_unsupported_str(str) == FAILURE)
		return (FAILURE);
	new_str = replace_variable(str, envp);
	if (new_str == FAILURE)
		return (puterr("parse: invalid $ format"));
	tokenize(&token_list, new_str);
	free(new_str);
	if (token_check(token_list) == FAILURE)
	{
		ft_lstclear(&token_list, delete_token);
		return (FAILURE);
	}
	parse_tree = syntax_pipeline(token_list);
	ft_lstclear(&token_list, delete_token);
	return (parse_tree);
}
