/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:48:31 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/03 16:03:20 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envp(char **envp, t_env **env_list)
{
	int		i;
	t_env	*env_node;

	i = 0;
	if (!envp[0])
	{
		g_exit_stat = 0;
		ft_exit(g_exit_stat);
	}
	while (envp[i + 1])
	{
		env_node = init_env_node(envp[i]);
		envlst_addback(env_list, env_node);
		i++;
	}
}

void	delete_node(t_env **env, t_env *temp, t_env *prev)
{
	if (temp == *env)
		(*env) = (*env)->next;
	else if (temp->next == NULL)
		prev->next = NULL;
	else
		prev->next = temp->next;
	free(temp->var);
	free(temp->value);
	free(temp);
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
	j = 0;
	shell->pipe_len -= 1;
	shell->pfd = alloc_pipe_fds(shell->pipe_len);
	shell->env_a = NULL;
	pid = pipex(shell, cmds);
	free_int_array(shell->pfd, shell->pipe_len);
	waitpid(pid, &j, 0);
	while (++i < shell->pipe_len)
		waitpid(-1, 0, 0);
	waitpid_signal(j, cmds, shell);
	unlink("a!");
}

int	pipex(t_infra *sh, t_cmd *cmds)
{
	int	fd[4];

	fd[3] = -1;
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = 0;
	if (sh->pipe_len > 0)
		pipe(sh->pfd[0]);
	while (++fd[3] < (sh->pipe_len + 1))
	{
		if ((fd[3] + 1) < sh->pipe_len)
			pipe(sh->pfd[fd[3] + 1]);
		if (sh->env_a)
			free_char_array(sh->env_a);
		sh->env_a = list_to_array(&sh->env_list);
		fd[2] = process(cmds, fd[3], sh, fd);
		if (heredoc_exist(cmds, fd[3]))
			waitpid(fd[2], 0, 0);
		if (fd[3] != 0 && sh->pipe_len > 0)
			close_fds(sh->pfd[fd[3] - 1][0], sh->pfd[fd[3] - 1][1], -1, -1);
	}
	free_char_array(sh->env_a);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (close_fds(fd[0], fd[1], -1, -1), fd[2]);
}
