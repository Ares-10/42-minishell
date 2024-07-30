/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:36 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 23:35:56 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static void	remove_env_var(char *var, char ***env);

int	builtin_unset(char **argv, char ***env)
{
	int	i;
	int	err_flag;

	i = 1;
	err_flag = FALSE;
	while (argv[i] != NULL)
	{
		if (*(argv[i]) == '\0')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("unset: ''", 2);
			ft_putendl_fd(": not a valid identifier", 2);
			err_flag = TRUE;
		}
		else if (ft_strcmp(argv[i], "?") != 0)
			remove_env_var(argv[i], env);
		i++;
	}
	return (err_flag);
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
