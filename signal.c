/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:36:18 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/03 13:37:33 by arafeeq          ###   ########.fr       */
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
				printf("Quit\n");
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
		(void)0;
	}
}
