/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:48 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 15:12:49 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_env(char **argv, char **env)
{
	int	i;

	if (argv[1] != NULL)
	{
		printf("env: %s: No such file or directory", argv[1]);
		return ;
	}
	// 0은 ? 있어서 제외
	i = 1;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
