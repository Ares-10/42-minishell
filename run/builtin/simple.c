/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:38:24 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 20:57:47 by seojepar         ###   ########.fr       */
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
	char	*msg;

	if (argv[1] == NULL)
		return ;
	if (chdir(argv[1]) == -1)
	{
		write_error("minishell: cd: ");
		perror(argv[1]);
	}
	// exit_status 추가 필요
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}
