/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:01:49 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/22 17:49:00 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	init_term(t_pipe *info, struct termios *term, char **line)
{
	if (dup2(info->original_stdin, STDIN_FILENO) == -1)
		pexit("dup2 failed");
	if (dup2(info->original_stdout, STDOUT_FILENO) == -1)
		pexit("dup2 failed");
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	signal(SIGINT, do_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	*line = NULL;
}

void	restore_term(struct termios *term, char **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	free(*env);
	*env = ft_strdup("?=0");
}

static void	readline_heredoc(t_redirect *redirect, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("\033[1A\033[2C", 1);
			break ;
		}
		if (ft_strcmp(line, redirect->file_path) == 0)
		{
			free(line);
			break ;
		}
		write(fd[W], line, strlen(line));
		write(fd[W], "\n", 1);
		free(line);
	}
	close(fd[W]);
}

void	heredoc_parent(char **env, int fd[2], pid_t pid)
{
	int	state;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &state, 0);
	state = WEXITSTATUS(state);
	if (state == 1)
	{
		g_sig = SIGINT;
		free(*env);
		*env = ft_strdup("?=1");
	}
	else if (state == 0)
	{
		free(*env);
		*env = ft_strdup("?=0");
	}
	set_signal();
	dup2(fd[R], STDIN_FILENO);
	close(fd[R]);
}

void	handle_heredoc(t_redirect *redirect, char **env, t_pipe *info)
{
	char			*line;
	int				fd[2];
	struct termios	term;
	pid_t			pid;

	if (g_sig == SIGINT)
		return ;
	if (pipe(fd) == -1)
		pexit("pipe failed");
	pid = fork();
	if (pid == -1)
		pexit("fork failed");
	if (pid == 0)
	{
		close(fd[R]);
		init_term(info, &term, &line);
		readline_heredoc(redirect, fd);
		restore_term(&term, env);
		exit (0);
	}
	else
	{
		close(fd[W]);
		heredoc_parent(env, fd, pid);
	}
}
