/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:26:38 by codespace         #+#    #+#             */
/*   Updated: 2024/07/30 23:48:44 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	set_env_zero(char **env, int val)
{
	char	*tmp;

	free(*env);
	tmp = ckm(ft_itoa(val));
	*env = ckm(ft_strjoin("?=", tmp));
	free(tmp);
}
