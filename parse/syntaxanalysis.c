/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxanalysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 10:21:00 by hyungcho          #+#    #+#             */
/*   Updated: 2024/06/30 10:21:00 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	syntax_analysis(t_tree **parse_tree, t_list *token_list)
{
	*parse_tree = NULL;
	*parse_tree = syntax_pipeline(token_list);
}
