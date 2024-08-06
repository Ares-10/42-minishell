/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:13:55 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/19 17:51:48 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 *  1. 데이터 초기화 (환경변수, 들고다닐 데이터변수)
 *  2. 프롬프트 찍기
 *  3. while문 실행
 *      -> 문자열 읽기
 *      -> 파싱하여 토큰화 하기
 *      -> 파싱한 데이터 검사하기
 *      -> 토큰화한 데이터로 실행시키기
 */

static void	set_term(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		puterr_exit("tcgetattr failed");
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term) == -1)
		puterr_exit("tcsetattr failed");
}

static char	**get_env(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	while (envp[++i])
		;
	env = (char **)xmalloc(sizeof(char *) * (i + 2));
	env[0] = ckm(ft_strdup("?=0"));
	i = -1;
	while (envp[++i])
		env[i + 1] = ckm(ft_strdup(envp[i]));
	env[i + 1] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	set_term();
	set_signal();
	start_shell(&env);
	exit(0);
}
