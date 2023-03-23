/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/23 18:28:20 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *cmd, int i, t_infra *shell, t_env **env_list)
{
	int		pid;
	char	**env_arr;

	pid = 0;
	if (cmd_is_built_in(cmd[i].main, 1))
		ft_built_in(cmd[i].main, cmd[i].cmd, env_list, 1);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env_arr = list_to_array(env_list);
			if (ft_strrchr(cmd[i].main, '/'))
				cmd[i].p = cmd[i].main;
			else
				cmd[i].p = check_path(shell->p_a, ft_strjoin("/", cmd[i].main));
			ft_dup2(shell, cmd, i);
			ft_pipe_dup2(shell, cmd, i);
			ft_close_pipes(shell, i, cmd[i]);
			if (cmd[i].cmd_len > 0)
			{
				mt_arg_error(cmd[i], env_arr, shell, cmd);
				if (cmd_is_built_in(cmd[i].main, 2))
					ft_built_in(cmd[i].main, cmd[i].cmd, env_list, 2);
				else if (cmd[i].p == NULL
					|| execve(cmd[i].p, cmd[i].cmd, env_arr) == -1)
					execve_error(shell, cmd, i, env_arr);
			}
			else
			{
				exit_stat = 0;
				ft_exit(0);
			}
		}
	}
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

void	ft_dup2(t_infra *shell, t_cmd *cmds, int i)
{
	int	k;
	int	fd;

	k = 0;
	while (k < cmds[i].red_len)
	{
		fd = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		if (cmds[i].red[k].flag != HERE_DOC)
		{
			if (fd == -1)
				fd_error(cmds[i].red[k].file, shell, cmds, i);
		}
		if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
			dup2(fd, STDIN_FILENO);
		if (cmds[i].red[k].flag == TRUNCATE || cmds[i].red[k].flag == APPEND)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		k++;
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
