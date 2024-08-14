/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:46:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/14 12:18:44 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_pwd(char **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		pexit("pwd failed due to directory issue");
	free(*env);
	*env = ckm(ft_strdup("?=0"));
}
