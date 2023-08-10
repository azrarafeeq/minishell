/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:48:31 by arafeeq           #+#    #+#             */
/*   Updated: 2023/08/10 18:11:05 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process(t_cmd *c, int i, t_infra *s, int *fd)
{
	if (cmd_is_built_in(c[0].main) && s->pipe_len == 0)
		return (parent_process(c, i, s));
	else
	{
		fd[2] = fork();
		if (fd[2] == 0)
		{
			signal(SIGQUIT, qhandler);
			close_fds(fd[0], fd[1], -1, -1);
			ft_pipe_dup2(s, c, i);
			if (c[i].cmd_len > 0)
			{
				mt_arg_error(s, c, i);
				if (cmd_is_built_in(c[i].main))
					ft_built_in(c[i], s, c);
				else if (!(c[i].p) || execve(c[i].p, c[i].cmd, s->env_a) == -1)
					execve_error(s, c, i);
			}
			free_shell_cmds_in_child(s, c);
		}
	}
	if (i != 0)
		close_fds(s->pfd[i - 1][0], s->pfd[i - 1][1], -1, -1);
	return (fd[2]);
}

void	ft_heredoc(t_red red, int in_fd, t_infra *shell)
{
	int		fd;
	char	*line;

	g_exit_stat = 0;
	signal(SIGINT, hd_handler);
	fd = open("a!", O_RDWR | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(in_fd);
	while (line)
	{
		if (g_exit_stat == 1 || ft_strcmp(red.file, line) == 0)
			break ;
		if (ft_strchr(line, DOL) && red.no_expand != 1)
			get_expanded(&line, shell, 0);
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(in_fd);
	}
	free(line);
	close(fd);
}

int	heredoc_exist(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (j < cmd[i].red_len)
	{
		if (cmd[i].red[j].flag == HERE_DOC)
			return (1);
		j++;
	}
	return (0);
}

int	ft_dup2(t_infra *shell, t_cmd *cmds, int i, int flag)
{
	int	fd[3];

	fd[2] = -1;
	fd[0] = dup(0);
	while (++fd[2] < cmds[i].red_len)
	{
		fd[1] = open_file(cmds[i].red[fd[2]], fd[0], shell);
		if (fd[1] == -1)
		{
			fd_error(cmds[i].red[fd[2]], shell, cmds, i);
			if (cmds[i].cmd_len > 0 && ft_strchr(cmds[i].main, '/') == 0
				&& !cmd_is_built_in(cmds[i].main))
				free(cmds[i].p);
			close(fd[0]);
			if (flag == 2)
				free_shell_cmds_in_child(shell, cmds);
			return (1);
		}
		if (cmds[i].red[fd[2]].flag == 0 || cmds[i].red[fd[2]].flag == 3)
			dup2(fd[1], STDIN_FILENO);
		if (cmds[i].red[fd[2]].flag == 1 || cmds[i].red[fd[2]].flag == 2)
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
