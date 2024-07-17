/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:41:30 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 23:11:15 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	change_env(char ***env, char *arg, int idx)
{
	free((*env)[idx]);
	(*env)[idx] = ft_strdup(arg);
	if ((*env)[idx] == NULL)
		puterr_exit("malloc failed");
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
	// 이렇게 하면, 딱 그.. env가 가리키고 있던 값 하나만 수정이 되겠지?
	return (1);
}

static int	find_key_in_env(char *key, char **env)
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

int	valid_shell_name(char *name)
{
	if (ft_isdigit(*name))
		return (FALSE);
	while (*name && *name != '=')
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

void	builtin_export(char **argv, char ***env, t_pipe *info)
{
	int		i;
	int		idx;
	char	*equal;
	char	*key;
	int		err_flag;

	key = NULL;
	err_flag = FALSE;
	if (argv[1] == NULL)
	{
		i = 0;
		while ((*env)[i++] != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd((*env)[i], 1);
		}
	}
	else
	{
		i = 1;
		while (argv[i] != NULL)
		{
			equal = ft_strchr(argv[i], '=');
			if (equal == argv[i] || !valid_shell_name(argv[i]))
			{
				err_flag = TRUE;
				write_error("minishell: export: ");
				write_error(argv[i]);
				write_error(": not a valid identifier\n");	
			}
			else if (equal != 0 && !info->prev_pipe_exist && !info->next_pipe_exist)
			{
				if (key != NULL)
					free(key);
				key = ft_substr(argv[i], 0, equal - argv[i] + 1);
				if (key == NULL)
					puterr_exit("malloc failed");
				idx = find_key_in_env(key, *env);
				if (idx < 0)
					ft_setenv(env, argv[i]);
				else
					change_env(env, argv[i], idx);
			}
			i++;
		}
		if (key != NULL)
			free(key);
	}
	// free((*env)[0]);
	// if (err_flag)
	// 	(*env)[0] = ft_strdup("?=1");
	// else
	// 	(*env)[0] = ft_strdup("?=0");
}
