/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:51:07 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/14 15:22:40 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
		if ((s[i] == c && check_quote(s, i) != 1) || i == 0)
			count++;
	if (s[0] == c)
		count++;
	return (count);
}

static char	*get_word(char const *s, const int i, char c)
{
	int		len;

	len = 1;
	while (s[len + i]
		&& !(s[len + i] == c && check_quote(s, len + i) != 1))
		len++;
	return (ckm(ft_substr(s, i, len)));
}

/* safe */
char	**nquote_split(char const *s, char c)
{
	char	**strs;
	int		j;
	int		i;

	strs = (char **)xmalloc(sizeof(char *) * (word_count(s, c) + 1));
	j = 0;
	i = 0;
	if (s[0] == c)
		strs[j] = ckm(ft_strdup(""));
	while (s[i] != '\0')
	{
		strs[j] = get_word(s, i, c);
		i += ft_strlen(strs[j]);
		j++;
	}
	strs[j] = NULL;
	return (strs);
}
