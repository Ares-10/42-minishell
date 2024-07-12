/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:33:06 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 18:58:55 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	execute_builtin(t_simplecmd *cmd, char **env, t_pipe *info)
{
	info->prev_pipe_exist = TRUE;
	if (ft_strcmp(cmd->file_path, "echo") == 0)
		builtin_echo(cmd->argv);
	else if (ft_strcmp(cmd->file_path, "cd") == 0)
		builtin_cd(cmd->argv, env);
	else if (ft_strcmp(cmd->file_path, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->file_path, "export") == 0)
		builtin_export(cmd->argv, &env);
	else if (ft_strcmp(cmd->file_path, "unset") == 0)
		builtin_unset(cmd->argv, &env);
	else if (ft_strcmp(cmd->file_path, "env") == 0)
		builtin_env(cmd->argv, env);
	else if (ft_strcmp(cmd->file_path, "exit") == 0)
		builtin_exit(cmd->argv);
	else
	{
		info->prev_pipe_exist = FALSE;
		return (0);
	}
	return (1);
}

void	pexit(char *msg)
{
	printf("%s", msg);
	exit(1);
}

void	wait_all_child(t_pipe *info, char **env)
{
	int		i;
	int		state;
	char	*exit_str;
	char	*new;

	i = 0;
	printf("loop start %d\n", info->total_child_cnt);
	while (i < info->total_child_cnt)
	{
		waitpid(-1, &state, 0);
		i++;
	}
	printf("loop end\n");
	// exit_str = ft_itoa(state);
	// if (!exit_str)
	// 	puterr_exit("Malloc Failed");
	// new = ft_strjoin("?=", exit_str);
	// if (!new)
	// {
	// 	free(exit_str);
	// 	puterr_exit("Malloc Failed");
	// }
	// ft_setenv(env, new);
	// free(new);
	// free(exit_str);
}

void	exec_command(t_tree *node, char **env, t_pipe *info)
{
	t_simplecmd	*cmd;
	int			new_fd[2];
	pid_t		pid;

	cmd = (t_simplecmd *)node->data;
	if (execute_builtin(cmd, env, info) == FALSE)
	{
		if (info->next_pipe_exist && pipe(new_fd) < 0)
			pexit("Pipe Failed");
		pid = fork();
		if (pid < 0)
			puterr_exit("Fork failed");
		if (pid == 0)
		{
			if (info->next_pipe_exist)
			{
				dup2(new_fd[W], STDOUT_FILENO);
				close(new_fd[R]);
				close(new_fd[W]);
			}
			exec_argv(cmd->file_path, cmd->argv, env);
		}
		else
		{
			info->total_child_cnt++;
			close(info->prev_fd[R]);
			close(info->prev_fd[W]);
			if (info->next_pipe_exist)
			{
				info->prev_fd[R] = new_fd[R];
				info->prev_fd[W] = new_fd[W];
				dup2(info->prev_fd[R], STDIN_FILENO);
				close(info->prev_fd[R]);
				close(info->prev_fd[W]);
			}
			else
				wait_all_child(info, env);
			info->prev_pipe_exist = TRUE;
		}
	}
}
