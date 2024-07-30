/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:55:56 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 23:56:40 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

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

void	handle_redirect(t_tree *node, char ***env, t_pipe *info)
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
		exec_heredoc(redirect, *env, info);
		return ;
	}
	if (fd < 0 && put_err_redirect(*env, redirect->file_path, info))
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
	int			state;

	cmd = (t_simplecmd *)node->data;
	if (!is_builtin(cmd->file_path))
	{
		signal(SIGINT, child_sig_handler);
		pid = fork();
		if (pid == 0)
			ft_execve(cmd->file_path, cmd->argv, *env);
		else
		{
			waitpid(pid, &state, 0);
			decode_waitpid(&state);
			set_env_zero(*env, state);
			set_signal();
		}
	}
	else
	{
		state = exec_builtin(cmd, env, info);
		set_env_zero(*env, state);
	}
}
