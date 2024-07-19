/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treebuilder2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:36:44 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/19 20:51:53 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	get_redirection_type(char *str);
static char	*get_file_path(t_list *token_list);
static char	**get_argv(t_list *token_list);

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

	if (token_list == NULL || ((t_token *)token_list->content)->type == T_PIPE)
		return (NULL);
	redirect = (t_redirect *)xmalloc(sizeof(t_redirect));
	token = (t_token *)token_list->content;
	redirect->type = get_redirection_type(token->str);
	token = (t_token *)token_list->next->content;
	redirect->file_path = ft_strdup(token->str);
	tree = (t_tree *)xmalloc(sizeof(t_tree));
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
	char		*file_path;

	file_path = get_file_path(token_list);
	if (file_path == NULL)
		return (NULL);
	cmd = (t_simplecmd *)xmalloc(sizeof(t_simplecmd));
	cmd->file_path = file_path;
	cmd->argv = get_argv(token_list);
	tree = (t_tree *)xmalloc(sizeof(t_tree));
	tree->type = T_SIMPLECMD;
	tree->left = NULL;
	tree->right = NULL;
	tree->data = cmd;
	return (tree);
}

/* safe */
char	*get_file_path(t_list *token_list)
{
	t_token		*token;
	char		*file_path;

	file_path = NULL;
	while (token_list && ((t_token *)token_list->content)->type != T_PIPE)
	{
		token = token_list->content;
		if (token->type == T_REDIRECT)
			token_list = token_list->next;
		else
		{
			if (file_path == NULL)
				file_path = ckm(ft_strdup(token->str));
			else if (!ft_strncmp(file_path, "env", 4))
			{
				free(file_path);
				file_path = ckm(ft_strdup(token->str));
			}
		}
		token_list = token_list->next;
	}
	return (file_path);
}

char	**get_argv(t_list *token_list)
{
	char		**argv;
	t_list		*t;
	int			i;

	i = 0;
	t = token_list;
	while (t && ((t_token *)t->content)->type != T_PIPE && ++i)
		t = t->next;
	argv = (char **)xmalloc(sizeof(char *) * (i + 1));
	argv[0] = NULL;
	i = -1;
	while (token_list && ((t_token *)token_list->content)->type != T_PIPE)
	{
		if (((t_token *)token_list->content)->type == T_REDIRECT)
		{
			token_list = token_list->next->next;
			continue ;
		}
		if (argv[0] && ft_strncmp(argv[0], "env", 4) == 0)
			free(argv[i--]);
		argv[++i] = ft_strdup(((t_token *)token_list->content)->str);
		token_list = token_list->next;
	}
	argv[++i] = NULL;
	return (argv);
}

/* safe */
int	get_redirection_type(char *str)
{
	if (ft_strncmp(str, ">", 2) == 0)
		return (OUTPUT_REDIRECT);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND_REDIRECT);
	if (ft_strncmp(str, "<", 2) == 0)
		return (INPUT_REDIRECT);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HERE_DOCUMENT);
	puterr_exit("get_redirection_type failed");
	return (FAILURE);
}
