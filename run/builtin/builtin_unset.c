/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:36 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 16:50:07 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	remove_env_var(char *var, char ***env);

void	builtin_unset(char **argv, char ***env)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "?") != 0)
			remove_env_var(argv[i], env);
		i++;
	}
}

static void	remove_env_var(char *var, char ***env)
{
	int	i;
	int	len;

	i = 0;
	len = strlen(var);
	while ((*env)[i] != NULL)
	{
		if (strncmp((*env)[i], var, len) == 0 && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			while ((*env)[i + 1] != NULL)
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			break ;
		}
		i++;
	}
}
