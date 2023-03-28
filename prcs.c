/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/28 14:33:08 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *cmd, int i, t_infra *shell, int *fd)
{
	int		pid;

	pid = 0;
	if (cmd_is_built_in(cmd[0].main) && shell->pipe_len == 0)
		return (parent_process(cmd, i, shell));
	else if (cmd[i].cmd_len > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			close_fds(fd[0], fd[1], -1, -1);
			ft_pipe_dup2(shell, cmd, i);
			if (cmd[i].cmd_len > 0)
			{
				mt_arg_error(shell, cmd, i);
				if (cmd_is_built_in(cmd[i].main))
					ft_built_in(cmd[i], &shell->env_list);
				else if (cmd[i].p == NULL
					|| execve(cmd[i].p, cmd[i].cmd, shell->env_arr) == -1)
					execve_error(shell, cmd, i);
				ft_exit(g_exit_stat);
			}
		}
	}
	return (pid);
}

void	ft_heredoc(char *delimeter)
{
	int		fd;
	char	*line;

	fd = open("a!", O_RDWR | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(delimeter, line) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
}

int	open_file(char *file, int flag)
{
	int	fd;

	fd = -1;
	if (flag == IN_FILE)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == TRUNCATE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == HERE_DOC)
	{
		ft_heredoc(file);
		fd = open("a!", O_RDONLY, 0777);
	}
	return (fd);
}

int	ft_dup2(t_infra *shell, t_cmd *cmds, int i, int flag)
{
	int	k;
	int	fd;

	k = 0;
	while (k < cmds[i].red_len)
	{
		fd = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		if (fd == -1 && cmds[i].red[k].flag != HERE_DOC)
		{
			fd_error(cmds[i].red[k].file, shell, cmds, i);
			if (flag == 2)
				ft_exit(g_exit_stat);
			return (1);
		}
		if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
			dup2(fd, STDIN_FILENO);
		if (cmds[i].red[k].flag == TRUNCATE || cmds[i].red[k].flag == APPEND)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		k++;
	}
	return (0);
}

void	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i)
{
	if (ft_strrchr(cmds[i].main, '/'))
		cmds[i].p = cmds[i].main;
	else
		cmds[i].p = check_path(path_array(get_path(&shell->env_list)),
				ft_strjoin("/", cmds[i].main));
	ft_dup2(shell, cmds, i, 2);
	if (shell->pipe_len > 0)
	{
		if (i == 0 || i == shell->pipe_len)
		{
			if (file_rd_exist(cmds[i], 1, 2) == 0 && i == 0)
				dup2(shell->pfd[0][1], STDOUT_FILENO);
			else if (file_rd_exist(cmds[i], 0, 3) == 0 && i == shell->pipe_len)
				dup2(shell->pfd[shell->pipe_len - 1][0], STDIN_FILENO);
		}
		else if (shell->pipe_len > 1)
		{
			if (file_rd_exist(cmds[i], 0, 3) == 0)
				dup2(shell->pfd[i - 1][0], STDIN_FILENO);
			if (file_rd_exist(cmds[i], 1, 2) == 0)
				dup2(shell->pfd[i][1], STDOUT_FILENO);
		}
	}
	ft_close_pipes(shell, i, cmds[i]);
}
