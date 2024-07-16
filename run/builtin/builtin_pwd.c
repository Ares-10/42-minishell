/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:46:50 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/16 16:47:00 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}
