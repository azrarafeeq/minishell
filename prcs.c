/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/26 16:14:24 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *c, int i, t_infra *shell, int *fd)
{
	int		pid;

	pid = 0;
	if (ft_pipe_dup2(shell, c, i) == 1)
		return (0);
	if (cmd_is_built_in(c[0].main) && shell->pipe_len == 0)
		ft_built_in(c[i], &shell->env_list);
	else if (c[i].cmd_len > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			process2(shell, c, i, &shell->env_list);
			if (c[i].cmd_len > 0)
			{
				mt_arg_error(c[i], shell->e_a, shell, c);
				if (cmd_is_built_in(c[i].main))
					ft_built_in(c[i], &shell->env_list);
				else if (!c[i].p || execve(c[i].p, c[i].cmd, shell->e_a) == -1)
					execve_error(shell, c, i, fd);
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

int	ft_dup2(t_cmd *cmds, int i)
{
	int	k;
	int	fd1;
	int	fd2;

	k = -1;
	while (++k < cmds[i].red_len)
	{
		fd1 = -2;
		fd2 = -2;
		if (cmds[i].red[k].flag == IN_FILE || cmds[i].red[k].flag == HERE_DOC)
			fd1 = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		else
			fd2 = open_file(cmds[i].red[k].file, cmds[i].red[k].flag);
		if (ft_dup2_part_2(cmds[i], k, fd1, fd2))
			return (1);
		if (fd2 != -2)
			dup2(fd1, STDIN_FILENO);
	}
	if (fd2 != -2)
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
