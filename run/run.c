/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:43:58 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/12 12:25:38 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	exec_tree(t_tree *node, char **env, t_pipe *info);
void	exec_command(t_tree *node, char **env, t_pipe *info);
void	handle_pipe(t_tree *node, char **env, t_pipe *info);
void	handle_redirect(t_tree *node, char **env, t_pipe *info);

void	init_pipe(t_pipe **info)
{
	*info = xmalloc(sizeof(t_pipe));
	if (pipe((*info)->prev_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	(*info)->prev_pipe_exist = FALSE;
}

void	search_tree(t_tree *node, char **env, t_pipe *info)
{
	exec_tree(node, env, info);
	if (node->left != NULL)
		search_tree(node->left, env, info);
	if (node->right != NULL)
		search_tree(node->right, env, info);
}

void	exec_tree(t_tree *node, char **env, t_pipe *info)
{
	if (node->type == T_SIMPLECMD)
		exec_command(node, env, info);
	if (node->type == T_PIPE)
		handle_pipe(node, env, info);
	if (node->type == T_REDIRECT)
		handle_redirect(node, env, info);
}

void	handle_pipe(t_tree *node, char **env, t_pipe *info)
{
	// 파이프를 만나면 해야할 일: 
	// 뒤에 파이프가 없다면 1로 리다이렉팅,
	// 뒤에 파이프가 있다면 파이프의 write로 리다이렉팅.
	// 앞에 파이프가 있었다면 그건 어차피 항상 0으로 왔을거라 알바 아님.
	// N개의 파이프가 새로 파이프를 만들기보다 파이프끼리 파이프를 공유해서
	// 사용할 수 있어야 함. 공유 파이프를 어떻게 전달할 것인가?
	// 포크를 떠서 프로세스 종료시까지 기다려야한다.
	// 그건 여기서 하지 말고, cmd 노드에서 포크 뜨고 실행시키는걸로 하자!
	// 왜냐면 포크를 뜨는 순간 프로세스가 복제가 되서 노드를 중복 순회할 수도.

	if (node->right)
		info->next_pipe_exist = TRUE;
	else
		info->next_pipe_exist = FALSE;
}

void	handle_here_document(t_redirect *redirect, char **env)
{
	char	*line;
	int		tmp_fd;
	char	*tmp_filename;

	line = NULL;
	// tmp_filename = tmpnam(NULL);
	tmp_filename = ".tmp";
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd < 0)
	{
		perror("Failed to open temporary file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			break ;
		}
		if (strcmp(line, redirect->file_path) == 0)
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
	{
		perror("Failed to reopen temporary file");
		exit(EXIT_FAILURE);
	}
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	unlink(tmp_filename);
}

void	handle_redirect(t_tree *node, char **env, t_pipe *info)
{
	t_redirect	*redirect;
	int			fd;

	redirect = (t_redirect *)node->data;
	if (redirect->type == OUTPUT_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect->type == APPEND_REDIRECT)
		fd = open(redirect->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redirect->type == INPUT_REDIRECT)
		fd = open(redirect->file_path, O_RDONLY);
	else if (redirect->type == HERE_DOCUMENT)
	{
		handle_here_document(redirect, env);
		return ;
	}
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (redirect->type == OUTPUT_REDIRECT || redirect->type == APPEND_REDIRECT)
		dup2(fd, STDOUT_FILENO);
	else if (redirect->type == INPUT_REDIRECT)
		dup2(fd, STDIN_FILENO);
	close(fd);
	if (node->right)
		exec_command(node->right, env, info);
}
