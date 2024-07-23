/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:33:54 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/23 15:51:52 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 커서 위치 요청: 
 * \033[6n 시퀀스를 터미널에 쓰면, 
 * 터미널은 현재 커서 위치를 ESC[n;mR 형식으로 응답한다.
 * 1. 터미널 속성 가져오기
 * 2. 로우 모드로 전환
 * 3. 커서 위치 요청
 * 4. 응답 파싱
 * 5. 원래 터미널 속성 복구
 */

static void	parse_cursor_position(char *buf, int *row, int *col)
{
	unsigned int	i;
	int				found_row;
	int				found_col;

	i = 2;
	found_row = 0;
	found_col = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (!found_row)
				*row = *row * 10 + (buf[i] - '0');
			else if (!found_col)
				*col = *col * 10 + (buf[i] - '0');
		}
		else if (buf[i] == ';')
			found_row = 1;
		i++;
	}
}

void	get_cursor_position(int *rows, int *cols)
{
	struct termios	orig_termios;
	struct termios	raw_termios;
	char			buf[32];
	unsigned int	i;

	*rows = 0;
	*cols = 0;
	i = 0;
	tcgetattr(STDIN_FILENO, &orig_termios);
	raw_termios = orig_termios;
	raw_termios.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
	write(STDOUT_FILENO, "\033[6n", 4);
	while (i < sizeof(buf) - 1)
	{
		if (read(STDIN_FILENO, buf + i, 1) != 1 || buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
	parse_cursor_position(buf, rows, cols);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
