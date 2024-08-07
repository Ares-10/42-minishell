/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:13:51 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/07 19:39:02 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "builtin.h"

void	put_declare_x(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[i], 1);
		i++;
	}
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

void	ft_addenv(char *key, char *val, char ***env)
{
	int	idx;

	idx = find_key_in_env(key, *env);
	if (idx < 0)
		ft_setenv(env, val);
	else
		change_env(env, val, idx);
}
