/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:47:21 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/23 12:08:59 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	init_str(char **str)
{
	if (*str)
		free(*str);
	*str = ckm(ft_strdup(""));
}

static void	custom_strjoin(char **first, char *second)
{
	char	*joined;

	joined = ckm(ft_strjoin(*first, second));
	free(*first);
	*first = joined;
}

static int	prompt(char *buf, char **total, int *first_read)
{
	int		bytes_read;
	char	*newline;

	if (*first_read)
	{
		ft_putstr_fd("> ", 1);
		*first_read = FALSE;
		init_str(total);
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
		*(newline) = '\0';
		*first_read = TRUE;
	}
	custom_strjoin(total, buf);
	return ((newline == NULL) + 1);
}

static void	readline_heredoc(t_redirect *redirect, int fd[2])
{
	char	buf[BUF_SIZE + 1];
	char	*total;
	int		first_read;
	int		result;

	total = NULL;
	first_read = TRUE;
	while (1)
	{
		result = prompt(buf, &total, &first_read);
		if (result == 0 || result == -1)
			break ;
		else if (result == 1 && ft_strcmp(total, redirect->file_path) == 0)
			break ;
		else if (result == 1)
			ft_putendl_fd(total, fd[W]);
	}
	if (total)
		free(total);
	close(fd[W]);
}

void	exec_heredoc(t_redirect *redirect, char **env, t_pipe *info)
{
	int				fd[2];
	int				old[2];
	struct termios	term;

	if (g_sig == SIGINT)
		return ;
	if (pipe(fd) == -1)
		pexit("pipe failed");
	save_load_io(old, SAVE);
	restore_io(*info);
	set_heredoc_signal(&term);
	readline_heredoc(redirect, fd);
	save_load_io(old, LOAD);
	dup2(fd[R], STDIN_FILENO);
	close(fd[R]);
	set_signal();
	sig_echo_on(&term);
	free(*env);
	*env = ft_strdup("?=0");
}
