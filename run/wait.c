/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:09:46 by seojepar          #+#    #+#             */
/*   Updated: 2024/08/07 16:33:08 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

static int	decode_exit(int state)
{
	if (WIFEXITED(state))
		state = WEXITSTATUS(state);
	else if (WIFSIGNALED(state))
	{
		if (WTERMSIG(state) == SIGINT)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			state = 130;
		}
		else if (WTERMSIG(state) == SIGQUIT)
		{
			ft_putendl_fd("Quit: 3", STDOUT_FILENO);
			state = 131;
		}
		else
			state = 128 + state;
	}
	return (state);
}

static void	wait_all(t_pipe *info, int *state, char **env)
{
	int	i;
	int	ret_wait;

	i = 0;
	ret_wait = 0;
	while (i < info->child_num)
	{
		while (ret_wait == 0)
		{
			ret_wait = waitpid(info->child_pids[i], state, 0);
			if (ret_wait == -1)
				pexit("waitpid error");
		}
		ret_wait = 0;
		i++;
	}
	if (info->builtin_last_flag)
		*state = ft_atoi(ft_getenv("?", env));
	else
		*state = decode_exit(*state);
}

void	wait_all_child(t_pipe *info, char **env)
{
	int		state;
	char	*tmp;

	if (info->child_num == 0 || g_sig == SIGINT)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_all(info, &state, env);
	free(*env);
	tmp = ckm(ft_itoa(state % 256));
	*env = ckm(ft_strjoin("?=", tmp));
	free(tmp);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
