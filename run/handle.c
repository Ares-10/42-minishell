/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:15:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/21 16:06:29 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	handle_pipe(t_tree *node, char **env, t_pipe *info)
{
	int	new_fd[2];

	info->io_flag = FALSE;
	if (info->next_pipe_exist)
		info->prev_pipe_exist = TRUE;
	if (info->prev_pipe_exist && dup2(info->prev_fd[R], STDIN_FILENO) == -1)
		pexit("dup2 failed");
	if (node->right)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
		info->next_pipe_exist = TRUE;
		if (pipe(new_fd) == -1)
			pexit("Pipe Failed");
		dup2(new_fd[W], STDOUT_FILENO);
		close(new_fd[W]);
		info->prev_fd[R] = new_fd[R];
	}
	else
	{
		info->next_pipe_exist = FALSE;
		if (dup2(info->original_stdout, STDOUT_FILENO) == -1)
			pexit("dup2 failed");
	}
}

static int	put_err_redirect(char **env, char *path, t_pipe *info)
{
	free(*env);
	*env = ckm(ft_strdup("?=1"));
	info->io_flag = TRUE;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (1);
}

void	handle_redirect(t_tree *node, char **env, t_pipe *info)
{
	t_redirect	*redirect;
	int			fd;

	redirect = (t_redirect *)node->data;
	if (redirect->type != HERE_DOCUMENT && info->io_flag)
		return ;
	if (redirect->type == OUTPUT_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == APPEND_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == INPUT_REDIRECT)
		fd = open(redirect->file_path, O_RDONLY);
	else
	{
		(void)fd;
		handle_heredoc(redirect, env, info);
		return ;
	}
	if (fd < 0 && put_err_redirect(env, redirect->file_path, info))
		return ;
	if (redirect->type == OUTPUT_REDIRECT || redirect->type == APPEND_REDIRECT)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == INPUT_REDIRECT)
		dup2(fd, STDIN_FILENO);
	close(fd);
}
