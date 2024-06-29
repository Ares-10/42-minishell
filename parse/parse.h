/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:23:19 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 04:23:29 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

int		get_token_size(const char *str);
t_token	*new_token(const char *str, int size);
void	delete_token(t_token *token);

int		check_quote(const char *str, int index);

#endif
