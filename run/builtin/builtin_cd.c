/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:45:29 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 23:50:22 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <dirent.h>

static char	*find_cdpath(char *dirname, char **env);
static void	set_env_pwd(char ***env, char *old_pwd, char *new_pwd);

void	put_error_cd(char *dest, char ***env)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (dest == NULL)
		ft_putstr_fd("HOME not set\n", 2);
	else
		perror(dest);
	free(**env);
	**env = ckm(ft_strdup("?=1"));
}

int	builtin_cd(char **argv, char ***env)
{
	char	old_pwd[1024];
	char	new_pwd[1024];
	char	*dest;

	getcwd(old_pwd, sizeof(old_pwd));
	if (argv[1] == NULL)
		dest = ft_getenv("HOME", *env);
	else
	{
		dest = find_cdpath(argv[1], *env);
		if (dest != NULL && chdir(dest) == 0)
			free(dest);
		dest = ckm(ft_strdup(argv[1]));
	}
	if (chdir(dest) == -1)
		put_error_cd(dest, env);
	else
	{
		getcwd(new_pwd, sizeof(new_pwd));
		set_env_pwd(env, old_pwd, new_pwd);
		return (0);
	}
	return (1);
}

int	dir_in_path(char *name, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(path);
	if (dirp == NULL)
		return (ERROR);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (ft_strcmp(dp->d_name, name) == 0)
		{
			(void)closedir(dirp);
			return (FOUND);
		}
		dp = readdir(dirp);
	}
	(void)closedir(dirp);
	return (NOT_FOUND);
}

static char	*find_cdpath(char *dirname, char **env)
{
	char	*cdpath_env;
	char	**split_path;
	char	*ret;
	int		i;

	cdpath_env = ft_getenv("CDPATH", env);
	if (cdpath_env == NULL)
		return (NULL);
	split_path = ckm(ft_split(cdpath_env, ':'));
	i = 0;
	while (split_path[i])
	{
		if (dir_in_path(dirname, split_path[i]))
		{
			ret = ft_strdup(split_path[i]);
			ft_free(split_path);
			return (ret);
		}
		i++;
	}
	ft_free(split_path);
	return (NULL);
}

static void	set_env_pwd(char ***env, char *old_pwd, char *new_pwd)
{
	char	*tmp_oldpwd;
	char	*tmp_newpwd;

	tmp_oldpwd = ckm(ft_strjoin("OLDPWD=", old_pwd));
	ft_setenv(env, tmp_oldpwd);
	free(tmp_oldpwd);
	tmp_newpwd = ckm(ft_strjoin("PWD=", new_pwd));
	ft_setenv(env, tmp_newpwd);
	free(tmp_newpwd);
}
