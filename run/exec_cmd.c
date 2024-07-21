/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:44:53 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/21 16:50:10 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parse.h"
#include <dirent.h>

static void	ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (ft_getenv("PATH", env) == NULL)
		return (cmd);
	allpath = ft_split(ft_getenv("PATH", env), ':');
	if (!allpath)
		exit(EXIT_FAILURE);
	while (allpath[++i])
	{
		if (allpath[i][ft_strlen(allpath[i]) - 1] == '/')
			path_part = ft_strdup(allpath[i]);
		else
			path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK) == 0 && access(exec, X_OK) == 0)
			return (exec);
		free(exec);
	}
	ft_free(allpath);
	return (cmd);
}

void	exec_argv(char *cmd, char **argv, char **env)
{
	char	*path;
	DIR		*dir;

	path = get_path(cmd, env);
	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
	else if (execve(path, argv, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
		ft_free(argv);
		if (errno == EPERM)
			exit(126);
		else
			exit(127);
	}
}

void	exec_command(t_tree *node, char ***env, t_pipe *info)
{
	t_simplecmd	*cmd;
	pid_t		pid;

	cmd = (t_simplecmd *)node->data;
	if (execute_builtin(cmd, env, info) == FALSE)
	{
		set_child_signal();
		pid = fork();
		if (pid < 0)
			puterr_exit("Fork failed");
		if (pid == 0)
			exec_argv(cmd->file_path, cmd->argv, *env);
		else
		{
			info->total_child_cnt++;
			set_signal();
		}
	}
	if (!info->next_pipe_exist)
		wait_all_child(info, *env);
}
