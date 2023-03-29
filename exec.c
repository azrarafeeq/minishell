/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:26:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/29 13:11:56 by arafeeq          ###   ########.fr       */
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
	p_fd = malloc(sizeof(int *) * pipe_amt);
	while (i < pipe_amt && pipe_amt <= INT_MAX)
	{
		p_fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (p_fd);
}

void	execute(t_infra *shell, t_cmd *cmds)
{
	int		i;
	int		j;
	int		pid;

	i = -1;
	shell->pipe_len -= 1;
	shell->pfd = alloc_pipe_fds(shell->pipe_len);
	pid = pipex(shell, cmds);
	free_int_array(shell->pfd, shell->pipe_len);
	waitpid(pid, &j, 0);
	while (++i < shell->pipe_len)
		waitpid(-1, 0, 0);
	waitpid_signal(j, cmds, shell);
	unlink("a!");
}

int	pipex(t_infra *shell, t_cmd *cmds)
{
	int	i;
	int	fd[2];
	int	pid;

	i = -1;
	fd[0] = dup(0);
	fd[1] = dup(1);
	shell->env_arr = NULL;
	if (shell->pipe_len > 0)
		pipe(shell->pfd[0]);
	while (++i < (shell->pipe_len + 1))
	{
		if ((i + 1) < shell->pipe_len)
			pipe(shell->pfd[i + 1]);
		if (shell->env_arr)
			free_char_array(shell->env_arr);
		shell->env_arr = list_to_array(&shell->env_list);
		pid = process(cmds, i, shell, fd);
		if (i != 0 && shell->pipe_len > 0)
			close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1], -1, -1);
	}
	free_char_array(shell->env_arr);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_fds(fd[0], fd[1], -1, -1);
	return (pid);
}

void	waitpid_signal(int j, t_cmd *cmds, t_infra *shell)
{
	if (!(cmd_is_built_in(cmds[0].main) && shell->pipe_len == 0)
		&& cmds[shell->pipe_len].cmd_len)
	{
		if (WIFEXITED(j))
			g_exit_stat = WEXITSTATUS(j);
		if (WIFSIGNALED(j))
		{
			g_exit_stat = WTERMSIG(j);
			g_exit_stat += 128;
		}
	}
}
