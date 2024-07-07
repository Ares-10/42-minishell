/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:33:06 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/07 22:33:53 by seojepar         ###   ########.fr       */
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

int	execute_builtin(t_simplecmd *cmd, char **env)
{
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
		builtin_env(env);
	else if (ft_strcmp(cmd->file_path, "exit") == 0)
		builtin_exit(cmd->argv);
	else
		return (0);
	return (1);
}

void	exec_command(t_tree *node, char **env)
{
	t_simplecmd	*cmd;

	cmd = (t_simplecmd *)node->data;
	if (execute_builtin(cmd, env) == FALSE)
		exec_argv(cmd->file_path, env);
}
