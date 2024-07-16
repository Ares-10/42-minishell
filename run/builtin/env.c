/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:48 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 15:00:50 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parse.h"

void	builtin_env(char **argv, char **env)
{
	int	i;

	if (argv[1] != NULL)
	{
		printf("env: %s: No such file or directory", argv[1]);
		free(env[0]);
		env[0] = ckm(ft_strdup("?=127"));
		return ;
	}
	// 0은 ? 있어서 제외
	i = 1;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	free(env[0]);
	env[0] = ckm(ft_strdup("?=0"));
}
