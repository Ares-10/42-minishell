/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:44:53 by seojepar          #+#    #+#             */
/*   Updated: 2024/06/30 21:58:35 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "libft.h"

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


static char	*my_getenv(char *name, char **env)
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
	// split에서 환경변수 자체가 없어서 실패할 경우(널 들어갈 경우)
	// 안 터지도록 함수 수정이 필요함. 
	allpath = ft_split(my_getenv("PATH", env), ':');
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

void	exec_argv(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found", 2);
		ft_free(s_cmd);
		exit(EXIT_FAILURE);
	}
}
