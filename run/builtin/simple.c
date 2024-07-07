/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/07 21:39:32 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_echo(char **argv)
{
	int	i;

	i = 1;
	if (argv[i])
	{
		printf("%s\n", argv[1]);
		if (argv[i + 1])
			printf(" ");
	}
}

void	builtin_cd(char **argv, char **env)
{
	if (chdir(argv[1]) != 0)
		perror("cd failed");
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}
