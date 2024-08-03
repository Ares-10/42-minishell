/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:15:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/03 21:24:11 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	handle_pipe(t_tree *node, char **env, t_pipe *info)
{
	int	new_fd[2];

	info->io_flag = FALSE;
	if (info->next_pipe_exist)
		info->prev_pipe_exist = TRUE;
	if (info->prev_pipe_exist)
	{
		safe_dup2(info->prev_fd[R], STDIN_FILENO);
		close(info->prev_fd[R]);
	}
	info->next_pipe_exist = FALSE;
	if (node->right)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
		info->next_pipe_exist = TRUE;
		if (pipe(new_fd) == -1)
			pexit("Pipe Failed");
		safe_dup2(new_fd[W], STDOUT_FILENO);
		close(new_fd[W]);
		info->prev_fd[R] = new_fd[R];
	}
	else
		safe_dup2(info->original_stdout, STDOUT_FILENO);
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
		exec_heredoc(redirect, env, info);
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

void	handle_cmd(t_tree *node, char ***env, t_pipe *info)
{
	t_simplecmd	*cmd;
	pid_t		pid;

	cmd = (t_simplecmd *)node->data;
	if (execute_builtin(cmd, env, info) == FALSE)
	{
		signal(SIGINT, child_sig_handler);
		pid = fork();
		if (pid < 0)
			puterr_exit("Fork failed");
		if (pid == 0 && (close(info->prev_fd[R]), 1))
			ft_execve(cmd->file_path, cmd->argv, *env);
		else
		{
			info->total_child_cnt++;
			set_signal();
		}
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	restore_io(*info);
	if (!info->next_pipe_exist)
		wait_all_child(info, *env);
}
