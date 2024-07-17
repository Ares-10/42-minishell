/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:48 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/17 23:10:30 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parse.h"

void	builtin_env(char **argv, char **env)
{
	int	i;

	if (argv[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		free(env[0]);
		env[0] = ckm(ft_strdup("?=127"));
		return ;
	}
	i = 1;
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], 2);
		i++;
	}
	free(env[0]);
	env[0] = ckm(ft_strdup("?=0"));
}
