/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:48 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 16:51:59 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "parse.h"

int	builtin_env(char **argv, char **env)
{
	int	i;

	if (argv[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	i = 1;
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
