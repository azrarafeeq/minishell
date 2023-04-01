/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:48:31 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/01 23:48:19 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *cmd, int i, t_infra *shell, int *fd)
{
	fd[2] = 0;
	if (cmd_is_built_in(cmd[0].main) && shell->pipe_len == 0)
		return (parent_process(cmd, i, shell));
	else
	{
		fd[2] = fork();
		if (fd[2] == 0)
		{
			close_fds(fd[0], fd[1], -1, -1);
			ft_pipe_dup2(shell, cmd, i);
			if (cmd[i].cmd_len > 0)
			{
				mt_arg_error(shell, cmd, i);
				if (cmd_is_built_in(cmd[i].main))
					ft_built_in(cmd[i], shell);
				else if (cmd[i].p == NULL
					|| execve(cmd[i].p, cmd[i].cmd, shell->env_arr) == -1)
					execve_error(shell, cmd, i);
			}
			free_shell_cmds_in_child(shell, cmd);
		}
	}
	if (i != 0)
		close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1], -1, -1);
	return (fd[2]);
}

void	handler2(int sig)
{
	int	flag;

	flag = (waitpid(-1, NULL, WNOHANG) == -1);
	if (flag && sig == SIGINT)
	{
		exit(0);
	}
}
void ft_signal(t_infra *shell, t_cmd *cmds)
{
	ft_putnbr_fd(*(int *)signal(SIGINT, handler2), 2);
}

void	ft_heredoc(char *delimeter, int in_fd, t_infra *shell, t_cmd *cmds)
{
	int		fd;
	char	*line;

	ft_signal(shell, cmds);
	fd = open("a!", O_RDWR | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(in_fd);
	while (line)
	{
		if (ft_strcmp(delimeter, line) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(in_fd);
	}
	free(line);
	close(fd);
}

int	ft_dup2(t_infra *shell, t_cmd *cmds, int i, int flag)
{
	int	k;
	int	fd[2];

	k = -1;
	fd[0] = dup(0);
	while (++k < cmds[i].red_len)
	{
		fd[1] = open_file(cmds[i].red[k], fd[0], shell, cmds);
		if (fd[1] == -1 && cmds[i].red[k].flag != HERE_DOC)
		{
			fd_error(cmds[i].red[k].file, shell, cmds, i);
			if (cmds[i].cmd_len > 0 && ft_strchr(cmds[i].main, '/') == 0)
				free(cmds[i].p);
			close(fd[0]);
			if (flag == 2)
				free_shell_cmds_in_child(shell, cmds);
			return (1);
		}
		if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
			dup2(fd[1], STDIN_FILENO);
		if (cmds[i].red[k].flag == TRUNCATE || cmds[i].red[k].flag == APPEND)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	return (close(fd[0]), 0);
}

void	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i)
{
	if (cmds[i].cmd_len > 0 && cmd_is_built_in(cmds[i].main) == 0)
	{
		if (ft_strrchr(cmds[i].main, '/'))
			cmds[i].p = cmds[i].main;
		else
			cmds[i].p = check_path(path_array(get_path(&shell->env_list)),
					ft_strjoin("/", cmds[i].main));
	}
	ft_dup2(shell, cmds, i, 2);
	if ((i == 0 || i == shell->pipe_len) && shell->pipe_len > 0)
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
	ft_close_pipes(shell, i, cmds[i]);
}
