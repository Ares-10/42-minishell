/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:45:29 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/21 16:53:49 by seojepar         ###   ########.fr       */
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

void	builtin_cd(char **argv, char ***env)
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
		free(**env);
		**env = ckm(ft_strdup("?=0"));
		set_env_pwd(env, old_pwd, new_pwd);
	}
}

int	dir_in_path(char *name, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

	dirp = opendir(path);
	if (dirp == NULL)
		return (ERROR);
	len = ft_strlen(name);
	dp = readdir(dirp);
	while (dp != NULL)
	{
		if (dp->d_namlen == len && ft_strcmp(dp->d_name, name) == 0)
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
			free_double(split_path);
			return (ret);
		}
		i++;
	}
	free_double(split_path);
	return (NULL);
}

/*
1. argv[1] 이 널인가?
	- 널이다: HOME 에 접근해서 패스로 가져온다. 
	- 널이 아니다: 2. /로 시작하는가? - 시작한다: 바로 패스로 사용
								- 시작안한다: CDPATH뒤에 슬래쉬를 붙여서 서치한다.
									- 성공했다면, 절대경로를 프린트해줘야한다.
	pwd를 새디렉토리로 바꾸고, oldpwd를 전 디렉토리로 세팅해준다.

원래는, /가 있는지 없는지 여부 등을 검사해서 조인하고 하려고 했는데
그냥 문득 생각해보니까 그냥 디렉토리를 두번 열면 되는거 아닌가? 해서 그렇게 로직을 바꿨다.
상대경로에서도 작동하더라고. chdir가.
*/

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
