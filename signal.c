/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:36:18 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/03 15:53:12 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitpid_signal(int j, t_cmd *cmds, t_infra *shell)
{
	if (!(cmd_is_built_in(cmds[0].main) && shell->pipe_len == 0)
		&& cmds[shell->pipe_len].cmd_len)
	{
		if (WIFEXITED(j))
			g_exit_stat = WEXITSTATUS(j);
		if (WIFSIGNALED(j))
		{
			if (WTERMSIG(j) == SIGINT)
				;
			else if (WTERMSIG(j) == SIGQUIT)
				write(2, "\n", 1);
			g_exit_stat += 128;
		}
	}
}

void	hd_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_stat = 1;
		write(2, "\nPress enter to exit\n", 21);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	qhandler(int sig)
{
	if (sig == SIGQUIT)
	{
	}
}

void	handler(int sig)
{
	int	flag;

	flag = (waitpid(-1, NULL, WNOHANG) == -1);
	if (flag && sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
