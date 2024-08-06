/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:53:58 by hyungcho          #+#    #+#             */
/*   Updated: 2024/08/04 15:45:53 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		dprintf(2, "main sig handler");
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGTERM)
		exit(0);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
}
