/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:02:44 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/26 05:58:01 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/signal.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

# define WORD 1
# define PIPE 2
# define REDIRECT 3

typedef struct s_token
{
	int				type;
	char			*str;
}	t_token;

void	set_signal(void);
void	start_shell(void);

void	parse(char *str);

void	puterr(char *msg);

#endif