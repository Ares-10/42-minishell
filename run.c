/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:29:55 by seojepar          #+#    #+#             */
/*   Updated: 2024/06/30 21:05:32 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * %%% CMD토큰타입만 찾아서 실행함, 또한 CMD단위의 구분은 |나 ;나 끝이 구분함 %%%
 * 1. 현재 CMD가 가지는 블록의 토큰들을 깨끗하게 바꿔줌
 * -> $VAL을 환경변수에서 찾아 문자열로 치환해서 넣어줌
 * -> 따옴표 제거
 * -> 음수로 처리했던 이스케이프 문자를 다시 양수로 토글함
 * 2. 현재 CMD블록의 이전 파이프가 있으면 dup2함 -> 하자마자 일반 fd를 close함
 * 3. 현재 CMD블록의 이후 파이프가 있으면 dup2함 -> 하자마자 일반 fd를 close함
 * 4. 현재 CMD블록 근처의 redirection을 처리함 -> open -> dup2 -> close
 * 	-> 2,3,4단계로 STDOUT, STDIN의 가르키는 파일이 바뀌었을 것
 * 	5. cmd를 만들어줌 -> CMD하나와 ARGS들을 char **로 만들어줌
 * 	6. exec함 (execve할 때는 fork해서 처리함)
 */

void	search_tree(t_ast *node)
{
	execute_tree(node);
	if (node->left != NULL)
		search_tree(node->left);
	if (node->right != NULL)
		search_tree(node->right);
}

void	execute_tree(t_ast *node)
{

}

// <pipeline>     ::= <cmd>
// 			|   <pipeline> '|' <cmd>
void	execute_pipe(t_ast *node)
{
	int	p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (node->left && node->right)
	{
		if (pipe(p_fd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid1 = fork();
		if (pid1 == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			close(p_fd[0]);
			dup2(p_fd[1], STDOUT_FILENO);
			close(p_fd[1]);
			search_tree(node->left);
			exit(EXIT_SUCCESS);
		}
		else
		{
			pid_t pid2 = fork();
			if (pid2 == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid2 == 0) {
				close(p_fd[1]);
				dup2(p_fd[0], STDIN_FILENO);
				close(p_fd[0]);
				search_tree(node->right);
				exit(EXIT_SUCCESS);
			}
			else
			{
				close(p_fd[0]);
				close(p_fd[1]);
				waitpid(pid1, NULL, 0);
				waitpid(pid2, NULL, 0);
			}
		}
	}
}

// <cmd>	::= <simple_cmd>
// 		|   <simple_cmd> <redirects>
void	execute_cmd(node)
{

}

// <simple_cmd>   ::= <file_path>
// 				   |   <argv>
void	execute_simple_cmd(node)
{

}

// <argv>	::= <file_path> <args>
void	execute_argv(node)
{

}

// <args>        ::= WORD
// 				| <args> WORD
// <filename>    ::= WORD
// <file_path>   ::= WORD
void	execute_file_path(node)
{

}

// <redirects>	::= <io_redirect>
// 			|  <redirects> <io_redirect>
void	execute_redirects(node)
{

}

// <io_redirect>  ::= '<'   <filename>
// 				|  '<<'  <filename>
// 				|  '>'   <filename>
// 				|  '>>'  <filename>
void	execute_io_redirect(node)
{

}