/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungcho <hyungcho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:15:13 by hyungcho          #+#    #+#             */
/*   Updated: 2024/07/17 19:35:51 by hyungcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	free_strs(char ***strs)
{
	int	i;

	i = -1;
	while ((*strs)[++i])
		free((*strs)[i]);
	free(*strs);
}

/* safe */
static char	*get_env_value(char *name, char **envp)
{
	int		i;
	char	*p;
	char	*env_value;

	i = -1;
	while (envp[++i] != NULL)
	{
		p = ft_strchr(envp[i], '=');
		if (p == NULL)
			continue ;
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0
			&& envp[i][ft_strlen(name)] == '=')
		{
			env_value = ckm(ft_strdup(p + 1));
			return (env_value);
		}
	}
	env_value = ckm(ft_strdup(""));
	return (env_value);
}

static int	get_var_name(char *str, char *var_name)
{
	int		i;
	int		j;
	int		brace_flag;

	brace_flag = 0;
	if (str[1] == '{')
		brace_flag = 1;
	i = 1 + brace_flag;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		var_name[j++] = str[i++];
	if (str[i] == '?' && i == 1 + brace_flag)
		var_name[j++] = str[i++];
	var_name[j] = '\0';
	if (brace_flag && str[i] != '}')
	{
		var_name[0] = '\0';
		return (FAILURE);
	}
	return (i + brace_flag);
}

/* safe */
static int	replace_var(char **str, char **envp)
{
	char	*env_value;
	char	*var_name;
	int		var_len;
	char	*tmp;

	if (!(ft_isalnum((*str)[1]) || (*str)[1] == '_'
		|| (*str)[1] == '{' || (*str)[1] == '?'))
		return (SUCCESS);
	var_name = (char *)xmalloc(ft_strlen(*str));
	var_len = get_var_name(*str, var_name);
	if (var_len == 0)
	{
		free(var_name);
		return (FAILURE);
	}
	env_value = get_env_value(var_name, envp);
	free(var_name);
	tmp = *str;
	*str = ckm(ft_strjoin(env_value, *str + var_len));
	free(tmp);
	free(env_value);
	return (SUCCESS);
}

/* safe */
char	*replace_variable(char *str, char **envp)
{
	int		i;
	char	*new_str;
	char	**strs;
	char	*tmp;

	strs = nquote_split(str, '$');
	i = -1;
	if (strs[0][0] != '$')
		new_str = ckm(ft_strdup(strs[++i]));
	else
		new_str = ckm(ft_strdup(""));
	while (strs[++i])
	{
		if (replace_var(&strs[i], envp) == FAILURE)
		{
			free_strs(&strs);
			free(new_str);
			return (FAILURE);
		}
		tmp = new_str;
		new_str = ckm(ft_strjoin(new_str, strs[i]));
		free(tmp);
	}
	free_strs(&strs);
	return (new_str);
}
