/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:43:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 17:24:43 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	exec_tree(t_tree *node, char ***env, t_pipe *info);
void	exec_command(t_tree *node, char ***env, t_pipe *info);
void	handle_pipe(t_tree *node, char **env, t_pipe *info);
void	handle_redirect(t_tree *node, char **env, t_pipe *info);

void	restore_io(t_pipe info)
{
	if (dup2(info.original_stdin, STDIN_FILENO) == -1)
		pexit("dup2 failed");
	if (dup2(info.original_stdout, STDOUT_FILENO) == -1)
		pexit("dup2 failed");
}

void	init_pipe(t_pipe **info)
{
	*info = xmalloc(sizeof(t_pipe));
	(*info)->total_child_cnt = 0;
	if (pipe((*info)->prev_fd) < 0)
		pexit("pipe failed");
	(*info)->prev_pipe_exist = FALSE;
	(*info)->next_pipe_exist = FALSE;
	(*info)->original_stdin = dup(STDIN_FILENO);
	(*info)->original_stdout = dup(STDOUT_FILENO);
	if ((*info)->original_stdin == -1 || (*info)->original_stdout == -1)
		pexit("dup failed");
}

void	search_tree(t_tree *node, char ***env, t_pipe *info)
{
	exec_tree(node, env, info);
	if (node->left != NULL)
		search_tree(node->left, env, info);
	if (node->right != NULL)
		search_tree(node->right, env, info);
}

void	exec_tree(t_tree *node, char ***env, t_pipe *info)
{
	if (node->type == T_SIMPLECMD && !info->io_flag)
		exec_command(node, env, info);
	if (node->type == T_PIPE)
		handle_pipe(node, *env, info);
	if (node->type == T_REDIRECT)
		handle_redirect(node, *env, info);
}

void	handle_pipe(t_tree *node, char **env, t_pipe *info)
{
	int	new_fd[2];

	info->io_flag = FALSE;
	if (info->next_pipe_exist)
		info->prev_pipe_exist = TRUE;
	if (info->prev_pipe_exist)
	{
		// 기존파이프의 R에서 가져오기
		if (dup2(info->prev_fd[R], STDIN_FILENO) == -1)
			pexit("dup2 failed");
	}
	if (node->right)
	{
		free(*env);
		*env = ckm(ft_strdup("?=0"));
		info->next_pipe_exist = TRUE;
		// 뒤에 파이프가 있으면, 출력을 새파이프의 W로 리다이렉팅
		// 					입력을 기존파이프의 R로 리다이렉팅
		// 4개를 항상 가지고 있어야되는데..
		if (pipe(new_fd) == -1)
			pexit("Pipe Failed");
		// 출력을 새파이프의 끝으로 할당.
		dup2(new_fd[W], STDOUT_FILENO);
		// 안쓰니까 폐기
		close(new_fd[W]);
		// 얘는 왜 닫음? 닫으면 안돼. 
		// close(new_fd[R]);
		info->prev_fd[R] = new_fd[R];
	}
	else
	{
		info->next_pipe_exist = FALSE;
		if (dup2(info->original_stdout, STDOUT_FILENO) == -1)
			pexit("dup2 failed");
	}
}

void	handle_here_document(t_redirect *redirect, char **en, t_pipe *info)
{
	char	*line;
	int		tmp_fd;
	char	*tmp_filename;
	struct termios	term;

	if (dup2(info->original_stdin, STDIN_FILENO) == -1)
		pexit("dup2 failed");
	// 에코 끔
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// 무시
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	// tmp_filename = tmpnam(NULL);
	tmp_filename = ".tmp";
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd < 0)
		pexit("Failed to open temporary file");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redirect->file_path) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd < 0)
		pexit("Failed to reopen temporary file");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	unlink(tmp_filename);
	// 시그널 복구
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// 에코 킴
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_redirect(t_tree *node, char **env, t_pipe *info)
{
	t_redirect	*redirect;
	int			fd;

	redirect = (t_redirect *)node->data;
	if (redirect->type != HERE_DOCUMENT && info->io_flag)
		return ;
	if (redirect->type == OUTPUT_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == APPEND_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == INPUT_REDIRECT)
		fd = open(redirect->file_path, O_RDONLY);
	else if (redirect->type == HERE_DOCUMENT)
	{
		handle_here_document(redirect, env, info);
		return ;
	}
	if (fd < 0)
	{
		free(*env);
		*env = ckm(ft_strdup("?=1"));
		info->io_flag = TRUE;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	if (redirect->type == OUTPUT_REDIRECT || redirect->type == APPEND_REDIRECT)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == INPUT_REDIRECT)
		dup2(fd, STDIN_FILENO);
	close(fd);
}
