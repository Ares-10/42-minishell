/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:43:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/04 14:54:05 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	restore_io(t_pipe info)
{
	safe_dup2(info.original_stdin, STDIN_FILENO);
	safe_dup2(info.original_stdout, STDOUT_FILENO);
}

void	save_load_io(int fd[2], int flag)
{
	if (flag == SAVE)
	{
		fd[0] = safe_dup(STDIN_FILENO);
		fd[1] = safe_dup(STDOUT_FILENO);
	}
	else if (flag == LOAD)
	{
		safe_dup2(fd[0], STDIN_FILENO);
		safe_dup2(fd[1], STDOUT_FILENO);
	}
}

void	init_pipe(t_pipe **info)
{
	*info = xmalloc(sizeof(t_pipe));
	(*info)->child_num = 0;
	if (pipe((*info)->prev_fd) < 0)
		pexit("pipe failed");
	(*info)->prev_pipe_exist = FALSE;
	(*info)->next_pipe_exist = FALSE;
	(*info)->original_stdin = safe_dup(STDIN_FILENO);
	(*info)->original_stdout = safe_dup(STDOUT_FILENO);
	(*info)->child_pids = NULL;
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
		handle_cmd(node, env, info);
	if (node->type == T_PIPE)
		handle_pipe(node, *env, info);
	if (node->type == T_REDIRECT)
		handle_redirect(node, *env, info);
}
