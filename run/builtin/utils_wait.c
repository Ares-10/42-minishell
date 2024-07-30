/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojepar <seojepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:51:19 by seojepar          #+#    #+#             */
/*   Updated: 2024/07/30 23:57:12 by seojepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	decode_waitpid(int *state)
{
	if (WIFEXITED(*state))
		*state = WEXITSTATUS(*state);
	else if (WIFSIGNALED(*state))
	{
		if (WTERMSIG(*state) == SIGINT)
			*state = 130;
		else if (WTERMSIG(*state) == SIGQUIT)
			*state = 131;
		else
			*state = 128 + *state;
	}
}

void	wait_all(t_pipe *info, int *state)
{
	int	i;

	i = 0;
	while (i < info->total_child_cnt)
	{
		waitpid(-1, state, 0);
		i++;
	}
	decode_waitpid(state);
}

void	wait_all_child(t_pipe *info, char **env)
{
	int	state;

	if (info->total_child_cnt == 0)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_all(info, &state);
	set_env_zero(env, state % 256);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
