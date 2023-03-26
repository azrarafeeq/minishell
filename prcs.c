/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/26 13:47:07 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *cmd, int i, t_infra *shell, t_env **env_list)
{
	int		pid;

	pid = 0;
	if (ft_pipe_dup2(shell, cmd, i) == 1)
		return (0);
	printf("hello\n");
	if (cmd_is_built_in(cmd[0].main) && shell->pipe_len == 0)
		ft_built_in(cmd[i], env_list);
	else if (cmd[i].cmd_len > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			process2(shell, cmd, i, env_list);
			if (cmd[i].cmd_len > 0)
			{
				mt_arg_error(cmd[i], shell->env_arr, shell, cmd);
				if (cmd_is_built_in(cmd[i].main))
					ft_built_in(cmd[i], env_list);
				else if (cmd[i].p == NULL
					|| execve(cmd[i].p, cmd[i].cmd, shell->env_arr) == -1)
					execve_error(shell, cmd, i, shell->env_arr);
				ft_exit(exit_stat);
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

int	ft_dup2(t_cmd *cmds, int i)
{
	int	k;
	int	fd1;
	int	fd2;

	k = 0;
	while (k < cmds[i].red_len)
	{
		fd1 = 42;
		fd2 = 42;
		if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
			fd1 = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		else
			fd2 = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		if (cmds[i].red[k].flag != HERE_DOC)
		{
			if (fd1 == -1 || fd2 == -1)
			{
				fd_error(cmds[i].red[k].file);
				return (1);
			}
		}
		if ((cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC) && k < cmds[i].red_len - 1)
			close(fd1);
		if ((cmds[i].red[k].flag == TRUNCATE || cmds[i].red[k].flag == APPEND) && k < cmds[i].red_len - 1)
			close(fd2);
		k++;
	}
	if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
		dup2(fd1, STDIN_FILENO);
	else
		dup2(fd2, STDOUT_FILENO);
	return (0);
}

int	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i)
{
	if (ft_dup2(cmds, i))
		return (1);
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
	return (0);
}
