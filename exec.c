/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:26:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/24 00:44:59 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envp(char **envp, t_env **env_list)
{
	int		i;
	t_env	*env_node;

	i = 0;
	while (envp[i + 1])
	{
		env_node = init_env_node(envp[i]);
		envlst_addback(env_list, env_node);
		i++;
	}
}

int	**alloc_pipe_fds(int pipe_amt)
{
	int	i;
	int	**p_fd;

	i = 0;
	//error message when reached the limit....but what is the limit??
	p_fd = malloc(sizeof(int *) * pipe_amt);
	while (i < pipe_amt)
	{
		p_fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (p_fd);
}

int	pipex(t_infra *shell, t_cmd *cmds, t_env *env_list)
{
	int	i;
	int	pid;

	i = 0;
	if (shell->pipe_len > 0)
		pipe(shell->pfd[0]);
	while (i < (shell->pipe_len + 1))
	{
		if ((i + 1) < shell->pipe_len)
			pipe(shell->pfd[i + 1]);
		pid = process(cmds, i, shell, &env_list);
		if (i != 0 && shell->pipe_len > 0)
			close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1], -1, -1);
		i++;
	}
	return (pid);
}

void	ft_close_pipes(t_infra *shell, int i, t_cmd cmd)
{
	if (shell->pipe_len > 0)
	{
		if (cmd.cmd_id == 1)
			close_fds(shell->pfd[0][0], shell->pfd[0][1], -1, -1);
		else if (cmd.cmd_id == (shell->pipe_len + 1))
		{
			close_fds(shell->pfd[shell->pipe_len - 1][0],
				shell->pfd[shell->pipe_len - 1][1], -1, -1);
		}
		else if (shell->pipe_len > 1)
		{
			close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1],
				shell->pfd[i][0], shell->pfd[i][1]);
		}
	}
}

/* void	waitpid_signal(int i)
{
	if (i == WIFEXITED)
	{
		exit_stat = 
	}
	if (i == WIFSIGNALED)
	{
		exit_stat = 
	}
	if (i == WIFSTOPPED)
	{
		exit_stat = 
	}
}
 */
