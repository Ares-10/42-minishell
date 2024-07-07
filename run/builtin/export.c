/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:41:30 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/07 22:32:51 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int	set_env_var(char *var, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	(*env)[i] = ft_strdup(var);
	(*env)[i + 1] = NULL;
	return (1);
}

void	builtin_export(char **argv, char ***env)
{
	if (argv[1] == NULL)
	{
		// for (int i = 0; (*env)[i] != NULL; i++)
		// 	printf("declare -x %s\n", (*env)[i]);
	}
	else
	{
		if (!set_env_var(argv[1], env))
			perror("export failed");
	}
}
