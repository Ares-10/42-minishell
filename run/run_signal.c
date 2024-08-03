/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:11:38 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/03 18:22:03 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "minishell.h"

static void	do_sigint_heredoc(int signum)
{
	g_sig = signum;
	ft_putendl_fd("", 1);
}

void	set_heredoc_signal(struct termios *term)
{
	struct sigaction	sa;

	sig_echo_off(term);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = do_sigint_heredoc;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	child_sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
	else if (sig == SIGTERM)
		exit(0);
}

void	sig_echo_off(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	sig_echo_on(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
