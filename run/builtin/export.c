/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:41:30 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 15:04:44 by seojepar         ###   ########.fr       */
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
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	(*env)[i] = ft_strdup(var);
	(*env)[i + 1] = NULL;
	return (1);
}

static int	find_key_in_env(char *key, char **env)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while(env[i] != NULL)
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
	while (*name != '=')
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

void	builtin_export(char **argv, char ***env)
{
	int		i;
	int		idx;
	char	*equal;
	char	*key;

	if (argv[1] == NULL)
	{
		i = 1;
		while((*env)[i] != NULL)
		{
			printf("declare -x %s\n", (*env)[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while(argv[i] != NULL)
		{
			equal = ft_strchr(argv[i], '=');
			if (equal == 0)
			{
				i++;
				continue ;
			}
			if (equal == argv[i])
			{
				write_error("minishell: export: ");
				write_error(argv[i]);
				write_error(": not a valid identifier\n");
				i++;
				continue ;
			}
			key = ft_substr(argv[i], 0, equal - argv[i] + 1);
			if (key == NULL)
				puterr_exit("malloc failed");
			if (valid_shell_name(key) == FALSE)
			{
				write_error("minishell: export: ");
				write_error(argv[i]);
				write_error(": not a valid identifier\n");
				i++;
				continue ;
			}
			idx = find_key_in_env(key, *env);
			if (idx < 0)
				ft_setenv(env, argv[i]);
			else
				change_env(env, argv[i], idx);
			i++;
		}
		if (i != 1)
			free(key);
	}
}
