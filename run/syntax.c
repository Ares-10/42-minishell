/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:04:19 by seojepar          #+#    #+#             */
/*   Updated: 2024/06/30 22:05:26 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
이 파일은 문법이 맞는지 여부를 확인하기 위한 함수들로 구성되어 있다.
블로그에 있던 함수틀을 일단 복사해왔다. 정확한 구현은 내일 할 예정.
*/

#include "minishell.h"

void	syntax_pipeline()
{
	syntax_cmd();
	if (token.type == T_PIPE)
		syntax_pipeline();
}

void	syntax_cmd()
{
	syntax_simple_cmd();
	if (token.type == T_REDIRECT)
		syntax_redirects();
}

void	syntax_redirects()
{
	syntax_io_redirect();
	if (token.type == T_REDIRECT)
		syntax_redirects();
}

void	syntax_io_redirect()
{
	if (token.type == T_REDIRECT && tokens.type == T_WORD)
		;
	else
		return (Fail);
}

void	syntax_simple_cmd()
{
	if (token.type == T_WORD)
	{
		if (token.type == T_WORD)
			;
	}
	else
		return (Fail);
}
