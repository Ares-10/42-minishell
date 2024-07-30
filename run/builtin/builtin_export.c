/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:41:30 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 18:21:14 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "builtin.h"

int	builtin_export(char **argv, char ***env, t_pipe *info)
{
	int		i;
	int		err_flag;

	err_flag = FALSE;
	if (argv[1] == NULL)
		put_declare_x(*env);
	else
	{
		i = 1;
		while (argv[i] != NULL)
			export_single(argv[i++], &err_flag, env, info);
	}
	return (err_flag);
}

void	export_single(char *arg, int *err_flag, char ***env, t_pipe *info)
{
	char	*key;
	int		idx;
	char	*equal;

	key = NULL;
	equal = ft_strchr(arg, '=');
	if (equal == arg || !valid_shell_name(arg))
	{
		*err_flag = TRUE;
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": not a valid identifier", 2);
	}
	else if (equal != 0 && !info->prev_pipe_exist \
	&& !info->next_pipe_exist)
	{
		key = ckm(ft_substr(arg, 0, equal - arg + 1));
		idx = find_key_in_env(key, *env);
		if (idx < 0)
			ft_setenv(env, arg);
		else
			change_env(env, arg, idx);
		free(key);
	}
}

int	ft_setenv(char ***env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new_env = xmalloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i] != NULL)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ckm(ft_strdup(var));
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (1);
}

void	change_env(char ***env, char *arg, int idx)
{
	free((*env)[idx]);
	(*env)[idx] = ckm(ft_strdup(arg));
}

int	find_key_in_env(char *key, char **env)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i] != NULL)
	{
		if (ft_strncmp(key, env[i], key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
