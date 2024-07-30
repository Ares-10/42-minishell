/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:15:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 23:56:21 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	tag_pipe_info(t_pipe *info, char **env, t_tree *node)
{
	info->io_flag = FALSE;
	if (info->next_pipe_exist)
		info->prev_pipe_exist = TRUE;
	if (node->right)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
		info->next_pipe_exist = TRUE;
	}
	else
		info->next_pipe_exist = FALSE;
}

static void	pipe_child(t_tree *node, char ***env, t_pipe *info, int new_fd[2])
{
	if (info->prev_pipe_exist)
	{
		safe_dup2(info->prev_fd[R], STDIN_FILENO);
		close(info->prev_fd[R]);
		close(info->prev_fd[W]);
	}
	if (info->next_pipe_exist)
	{
		safe_dup2(new_fd[W], STDOUT_FILENO);
		close(new_fd[W]);
		close(new_fd[R]);
	}
	else
		safe_dup2(info->original_stdout, STDOUT_FILENO);
	search_tree(node->left, env, info);
	exit(ft_atoi(ft_getenv("?", *env)));
}

void	pipe_parent(t_tree *node, char ***env, t_pipe *info, int new_fd[2])
{
	close(info->prev_fd[R]);
	close(info->prev_fd[W]);
	if (info->next_pipe_exist)
	{
		info->prev_fd[R] = new_fd[R];
		info->prev_fd[W] = new_fd[W];
	}
	info->total_child_cnt++;
	set_signal();
	if (node->right)
		exec_node(node->right, env, info);
}

void	handle_pipe(t_tree *node, char ***env, t_pipe *info)
{
	pid_t	pid;
	int		new_fd[2];

	tag_pipe_info(info, *env, node);
	if (!info->next_pipe_exist && !info->prev_pipe_exist)
	{
		search_tree(node->left, env, info);
		return ;
	}
	if (info->next_pipe_exist && pipe(new_fd) == -1)
		pexit("Pipe Failed");
	pid = fork();
	if (pid < 0)
		puterr_exit("Fork failed");
	if (pid == 0)
		pipe_child(node, env, info, new_fd);
	else
		pipe_parent(node, env, info, new_fd);
}
