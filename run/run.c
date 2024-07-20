/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:43:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 18:16:13 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	exec_tree(t_tree *node, char ***env, t_pipe *info);
void	exec_command(t_tree *node, char ***env, t_pipe *info);
void	handle_pipe(t_tree *node, char **env, t_pipe *info);
void	handle_redirect(t_tree *node, char **env, t_pipe *info);

void	restore_io(t_pipe info)
{
	if (dup2(info.original_stdin, STDIN_FILENO) == -1)
		pexit("dup2 failed");
	if (dup2(info.original_stdout, STDOUT_FILENO) == -1)
		pexit("dup2 failed");
}

void	init_pipe(t_pipe **info)
{
	*info = xmalloc(sizeof(t_pipe));
	(*info)->total_child_cnt = 0;
	if (pipe((*info)->prev_fd) < 0)
		pexit("pipe failed");
	(*info)->prev_pipe_exist = FALSE;
	(*info)->next_pipe_exist = FALSE;
	(*info)->original_stdin = dup(STDIN_FILENO);
	(*info)->original_stdout = dup(STDOUT_FILENO);
	if ((*info)->original_stdin == -1 || (*info)->original_stdout == -1)
		pexit("dup failed");
}

void	search_tree(t_tree *node, char ***env, t_pipe *info)
{
	exec_tree(node, env, info);
	if (node->left != NULL)
		search_tree(node->left, env, info);
	if (node->right != NULL)
		search_tree(node->right, env, info);
}

void	exec_tree(t_tree *node, char ***env, t_pipe *info)
{
	if (node->type == T_SIMPLECMD && !info->io_flag)
		exec_command(node, env, info);
	if (node->type == T_PIPE)
		handle_pipe(node, *env, info);
	if (node->type == T_REDIRECT)
		handle_redirect(node, *env, info);
}

void	init_exit_sig(char **env)
{
	if (g_sig == SIGINT)
	{
		free(*env);
		*env = ckm(ft_strdup("?=1"));
	}
}
