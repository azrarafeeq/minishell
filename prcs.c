/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/20 14:43:53 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd **cmd, int i, t_infra *shell, t_env **env_list)
{
	int		pid;
	char	**env_arr;

	pid = 0;
	if (ft_strcmp(cmd[i]->main, "exit") == 0 || ft_strcmp(cmd[i]->main, "cd") == 0
		|| ft_strcmp(cmd[i]->main, "export") || ft_strcmp(cmd[i]->main, "unset") == 0)
		ft_built_in(cmd[i]->main, cmd[i]->cmd, env_list);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			env_arr = list_to_array(&(shell->env_list));
			if (ft_strrchr(cmd[i]->main, '/'))
				cmd[i]->path = cmd[i]->main;
			else
				cmd[i]->path = check_path(shell->path_array, ft_strjoin("/", cmd[i]->main));
			ft_dup2(cmd[i]->red, cmd[i]->red_len, shell, cmd);
			if (file_rd_exist(cmd[i], 0, 1) == 0 && cmd[i]->cmd_id != 1)
				dup2(shell->pfd[i][0], STDIN_FILENO);
			if (file_rd_exist(cmd[i], 2, 3) == 0 && (cmd[i]->cmd_id != shell->pipe_len && cmd[i]->cmd_id != 1))
				dup2(shell->pfd[i + 1][1], STDOUT_FILENO);
			if (file_rd_exist(cmd[i], 2, 3) == 0 && cmd[i]->cmd_id == 1)
				dup2(shell->pfd[i][0], STDOUT_FILENO);
			if (shell->pipe_len > 1)
				close_fds(shell->pfd[i][0], shell->pfd[i][0], -1, -1);
			if (cmd[i]->cmd_id != 1 && cmd[i]->cmd_id != shell->pipe_len)
				close_fds(shell->pfd[i + 1][0], shell->pfd[i + 1][1], -1, -1);
			mt_arg_error(cmd[i], env_arr, shell);
			if (cmd_is_built_in(cmd[i]->main))
				ft_built_in(cmd[i]->main, cmd[i]->cmd, &(shell->env_list));
			else if (cmd[i]->path == NULL || execve(cmd[i]->path, cmd[i]->cmd, env_arr) == -1)
				execve_error(shell, cmd, i);
		}
	}
	close_fds(shell->pfd[i][0], shell->pfd[i][0], -1, -1);
	return (pid);
}

int	ft_heredoc(char *delimeter)
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
	return (fd);
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
		fd = ft_heredoc(file);
	return (fd);
}

void	ft_dup2(t_red *redirect, int red_len, t_infra *shell, t_cmd **cmds)
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
		else if (redirect[i].flag == TRUNCATE || redirect[i].flag == APPEND)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		i++;
	}
}
