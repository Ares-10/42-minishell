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

void	set_signal(void);
void	start_shell(void);

void	puterr(char *msg);

#endif