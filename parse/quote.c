/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:29:57 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 05:29:23 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
 * 열림 및 닫힘: -1
 * 따옴표 바깥쪽: 0
 * ' 안쪽: 1
 * " 안쪽: 2
 */
int	check_quote(const char *str, int index)
{
	int	i;
	int	quote_flag;
	int	dquote_flag;

	quote_flag = 0;
	dquote_flag = 0;
	i = -1;
	while (str[++i] && i != index)
	{
		if (str[i] == '\'' && !dquote_flag)
			quote_flag = !quote_flag;
		else if (str[i] == '\"' && !quote_flag)
			dquote_flag = !dquote_flag;
	}
	if (((str[i] == '\'' || str[i] == '\"') && (!quote_flag && !dquote_flag))
		|| (quote_flag && str[i] == '\'')
		|| (dquote_flag && str[i] == '\"'))
		return (-1);
	if (quote_flag)
		return (1);
	if (dquote_flag)
		return (2);
	return (0);
}
