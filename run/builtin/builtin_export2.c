/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:13:51 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/07 19:59:17 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include "builtin.h"

static void bubble_sort_indices(char *arr[], int indices[], int n)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	while (i < n-1)
	{
		j = 1;
		while (j < n - i - 1)
		{
			if (ft_strcmp(arr[indices[j]], arr[indices[j+1]]) > 0)
			{
				tmp = indices[j];
				indices[j] = indices[j+1];
				indices[j+1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	put_declare_x(char **env)
{
	int		i;
	int		cnt;
	char	*tmp;
	int		*idxs;

	cnt = 0;
	while (env[cnt] != NULL)
		cnt++;
	idxs = (int *)ckm(malloc(cnt * sizeof(int)));
	i = 0;
	while (i < cnt)
	{
		idxs[i] = i;
		i++;
	}
	bubble_sort_indices(env, idxs, cnt);
	i = 1;
	while (env[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[idxs[i]], 1);
		i++;
	}
	free(idxs);
}

int	valid_shell_name(char *name)
{
	if (ft_isdigit(*name))
		return (FALSE);
	while (*name && *name != '=')
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

void	ft_addenv(char *key, char *val, char ***env)
{
	int	idx;

	idx = find_key_in_env(key, *env);
	if (idx < 0)
		ft_setenv(env, val);
	else
		change_env(env, val, idx);
}
