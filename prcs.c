/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/21 22:08:00 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *cmd, int i, t_infra *shell, t_env **env_list)
{
	int		pid;
	char	**env_arr;

	pid = 0;
	if (ft_strcmp(cmd[i].main, "exit") == 0 || ft_strcmp(cmd[i].main, "cd") == 0
		|| ft_strcmp(cmd[i].main, "export") == 0 || ft_strcmp(cmd[i].main, "unset") == 0)
		ft_built_in(cmd[i].main, cmd[i].cmd, env_list);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			//printf("The id of command = %d\n", cmd[i].cmd_id);
			env_arr = list_to_array(env_list);
			if (ft_strrchr(cmd[i].main, '/'))
				cmd[i].path = cmd[i].main;
			else
				cmd[i].path = check_path(shell->path_array, ft_strjoin("/", cmd[i].main));
			//printf("cmd[i].path = %s\n", cmd[i].path);
			ft_dup2(cmd[i].red, cmd[i].red_len, shell, cmd);
			ft_pipe_dup2(shell, cmd, i);
			ft_close_pipes(shell, i, cmd[i]);
			if (cmd[i].cmd_len > 0)
			{
				mt_arg_error(cmd[i], env_arr, shell);
				if (cmd_is_built_in(cmd[i].main))
					ft_built_in(cmd[i].main, cmd[i].cmd, &(shell->env_list));
				else if (cmd[i].path == NULL || execve(cmd[i].path, cmd[i].cmd, env_arr) == -1)
					execve_error(shell, cmd, i);
			}
			exit(0);
		}
	}
	if (cmd[i].cmd_id != 1 && shell->pipe_len > 0)
		close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1], -1, -1);
	return (pid);
}

void	ft_heredoc(char *delimeter)
{
	int		fd;
	char	*line;

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
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
		fd = open("temp", O_RDONLY, 0777);
	}
	return (fd);
}

void	ft_dup2(t_red *redirect, int red_len, t_infra *shell, t_cmd *cmds)
{
	int	i;
	int	fd;

	i = 0;
	while (i < red_len)
	{
		fd = open_file(redirect[i].file, redirect[i].flag);
		if (redirect[i].flag != HERE_DOC)
			fd_error(fd, redirect[i].file, shell, cmds);
		if (redirect[i].flag == IN_FILE || redirect[i].flag == HERE_DOC)
			dup2(fd, STDIN_FILENO);
		if (redirect[i].flag == TRUNCATE || redirect[i].flag == APPEND)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		i++;
	}
}

void	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i)
{
	if (shell->pipe_len > 0)
	{
		if (cmds[i].cmd_id == 1 || cmds[i].cmd_id == (shell->pipe_len + 1))
		{
			if (file_rd_exist(cmds[i], 2, 3) == 0 && cmds[i].cmd_id == 1)
				dup2(shell->pfd[0][1], STDOUT_FILENO);
			if (file_rd_exist(cmds[i], 0, 1) == 0
				&& cmds[i].cmd_id == (shell->pipe_len + 1))
				dup2(shell->pfd[shell->pipe_len - 1][0], STDIN_FILENO);
		}
		else if (shell->pipe_len > 1)
		{
			if (file_rd_exist(cmds[i], 0, 1) == 0)
				dup2(shell->pfd[i - 1][0], STDIN_FILENO);
			if (file_rd_exist(cmds[i], 2, 3) == 0)
				dup2(shell->pfd[i][1], STDOUT_FILENO);
		}
	}
}

void ft_close_pipes(t_infra *shell, int i, t_cmd cmd)
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
