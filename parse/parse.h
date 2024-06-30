/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:23:19 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 09:06:55 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

# define WORD 0
# define PIPE 1
# define REDIRECT 2

void	tokenize(t_list **token_list, char *str);

void	delete_token(void *token);
int		check_quote(const char *str, int index);

#endif
