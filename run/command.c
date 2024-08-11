/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   command.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: seojepar <seojepar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/30 21:44:53 by seojepar		  #+#	#+#			 */
/*   Updated: 2024/08/07 17:26:14 by seojepar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "run.h"
#include "parse.h"
#include <dirent.h>

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

char	*access_check(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if ((dir != NULL && (closedir(dir), 1)) \
	|| access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit (127);
	}
	return (cmd);
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
	return (access_check(cmd));
}

static void	check_path(char *cmd)
{
	DIR	*dir;

	if (access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit (127);
	}
	dir = opendir(cmd);
	if (dir != NULL && (closedir(dir), 1))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit (126);
	}
}

void	ft_execve(char *cmd, char **argv, char **env)
{
	char	*path;

	if (cmd && (cmd[0] == '/' || cmd[0] == '.'))
		path = cmd;
	else
		path = get_path(cmd, env);
	check_path(path);
	if (execve(path, argv, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_free(argv);
		if (errno != 2)
		{
			perror(cmd);
			exit(126);
		}
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
}
