/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:46:18 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/07 22:34:22 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	builtin_exit(char **argv)
{
	int	status;

	status = 0;
	if (argv[1] != NULL)
		status = atoi(argv[1]);
	exit(status);
}
