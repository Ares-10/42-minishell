/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:47:21 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/22 23:17:33 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int	handle_input(char *buf, char **total, int *first_read)
{
	int		bytes_read;
	char	*newline;
	char	*new_total;

	if (*first_read)
	{
		ft_putstr_fd("> ", 1);
		*first_read = 0;
	}
	if (g_sig == SIGINT)
		return (-1);
	bytes_read = read(1, buf, BUF_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buf[bytes_read] = '\0';
	newline = ft_strchr(buf, '\n');
	if (newline)
	{
		*newline = '\0';
		*first_read = 1;
	}
	new_total = ckm(ft_strjoin(*total, buf));
	free(*total);
	*total = new_total;
	return ((newline != NULL) + 1);
}

static void	finalize_heredoc(int fd[2], char **total)
{
	write(fd[W], *total, strlen(*total));
	write(fd[W], "\n", 1);
	free(*total);
	close(fd[W]);
}

static void	readline_heredoc(t_redirect *redirect, int fd[2])
{
	char	buf[BUF_SIZE + 1];
	char	*total;
	int		first_read;
	int		result;

	total = ckm(ft_strdup(""));
	first_read = 1;
	while (1)
	{
		result = handle_input(buf, &total, &first_read);
		if (result == 0 || result == -1)
			break ;
		if (result == 1 && ft_strcmp(total, redirect->file_path) == 0)
		{
			finalize_heredoc(fd, &total);
			total = ckm(ft_strdup(""));
		}
	}
	finalize_heredoc(fd, &total);
}

static void	set_heredoc_signal(struct termios *term)
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

void	handle_heredoc(t_redirect *redirect, char **env, t_pipe *info)
{
	int				fd[2];
	struct termios	term;

	if (g_sig == SIGINT)
		return ;
	if (pipe(fd) == -1)
		pexit("pipe failed");
	restore_io(*info);
	set_heredoc_signal(&term);
	readline_heredoc(redirect, fd);
	dup2(fd[R], STDIN_FILENO);
	close(fd[R]);
	set_signal();
	sig_echo_on(&term);
	free(*env);
	*env = ft_strdup("?=0");
}
