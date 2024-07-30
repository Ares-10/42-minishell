/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:33:06 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 23:58:04 by seojepar         ###   ########.fr       */
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

int	is_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(name, "exit") == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	exec_builtin(t_simplecmd *cmd, char ***env, t_pipe *info)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(cmd->file_path, "echo") == 0)
		exit_status = builtin_echo(cmd->argv);
	else if (ft_strcmp(cmd->file_path, "cd") == 0)
		exit_status = builtin_cd(cmd->argv, env);
	else if (ft_strcmp(cmd->file_path, "pwd") == 0)
		exit_status = builtin_pwd();
	else if (ft_strcmp(cmd->file_path, "export") == 0)
		exit_status = builtin_export(cmd->argv, env, info);
	else if (ft_strcmp(cmd->file_path, "unset") == 0)
		exit_status = builtin_unset(cmd->argv, env);
	else if (ft_strcmp(cmd->file_path, "env") == 0)
		exit_status = builtin_env(cmd->argv, *env);
	else if (ft_strcmp(cmd->file_path, "exit") == 0)
		exit_status = builtin_exit(cmd->argv, *env);
	return (exit_status);
}
