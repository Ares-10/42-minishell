/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:29:55 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/01 11:27:33 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

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

void	search_tree(t_tree *node, char **env)
{
	exec_tree(node);
	if (node->left != NULL)
		search_tree(node->left);
	if (node->right != NULL)
		search_tree(node->right);
}

void	exec_tree(t_tree *node)
{
	if (node->type == T_NULL)
		return ;
	if (node->type == T_WORD)
		return ;
	if (node->type == T_PIPE)
		exec_pipe(node);
	if (node->type == T_REDIRECT)
		exec_redirects(node);
}

// <pipeline>     ::= <cmd>
// 			|   <pipeline> '|' <cmd>
void	exec_pipe(t_tree *node)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	// pipe가 자손에 있을 경우(노드의 왼/오 모두 존재)
	// 리다이렉팅 필수
	// pipe가 자손에 없는 경우 굳이 파이프 리다이렉팅이 필요하지 않다.
	if (node->left && node->right)
	{
		// 파이프 생성
		if (pipe(p_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		// 명령어 실행을 위해 프로세스 복제, 생성
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		// 자식 프로세스일 경우
		if (pid1 == 0)
		{
			close(p_fd[0]);
			// out을 파이프의 쓰는 쪽으로 바꿈
			dup2(p_fd[1], STDOUT_FILENO);
			close(p_fd[1]);
			search_tree(node->left);
			exit(EXIT_SUCCESS);
		}
		else
		{
			// 또 포크를 떠서 뒤 프로세스 실행
			pid_t pid2 = fork();
			if (pid2 == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid2 == 0) {
				close(p_fd[1]);
				// in을 파이프의 읽는 쪽으로 바꿈
				dup2(p_fd[0], STDIN_FILENO);
				close(p_fd[0]);
				search_tree(node->right);
				exit(EXIT_SUCCESS);
			}
			else
			{
				// 두 프로세스가 모두 종료될떄까지 대기
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
void	exec_cmd(t_tree *node)
{
	
	// 자체적으로 할건 없음.
	exec_tree(node->left);
	exec_tree(node->right);
}

// <simple_cmd>   ::= <file_path>
// 				   |   <argv>
void	exec_simple_cmd(t_tree *node)
{
	// left에 file_path, right에 argv를 가질것임.
	// <file_path>   ::= WORD
	// <argv>	::= <file_path> <args>
	// 얘네 둘은 별도의 함수가 필요없을것이라 판단함.
	// Q: envp는 어디서 받아오지?
	exec_argv(node->right->token.str, envp);
}

// <args>        ::= WORD
// 				| <args> WORD
// <filename>    ::= WORD

// <redirects>	::= <io_redirect>
// 			|  <redirects> <io_redirect>
void	exec_redirects(t_tree *node)
{
	// 확인이 필요할려나.. 토큰이 맞는건지에 대해서..?
	// 문법 확인을 여기서 해도 되겠다..!
}

// <io_redirect>  ::= '<'   <filename>
// 				|  '<<'  <filename>
// 				|  '>'   <filename>
// 				|  '>>'  <filename>
void	exec_io_redirect(t_tree *node)
{

}