/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:46:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 16:58:42 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_pwd(char **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		free(*env);
		*env = ckm(ft_strdup("?=0"));
	}
	else
	{
		perror("pwd failed");
		free(*env);
		*env = ckm(ft_strdup("?=1"));
	}
}
