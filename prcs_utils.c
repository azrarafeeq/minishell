/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/03 17:40:38 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_red red, int in_fd, t_infra *shell)
{
	int	fd;

	fd = -1;
	if (red.flag == IN_FILE)
		fd = open(red.file, O_RDONLY, 0777);
	else if (red.flag == TRUNCATE)
		fd = open(red.file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (red.flag == APPEND)
		fd = open(red.file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (red.flag == HERE_DOC)
	{
		ft_heredoc(red, in_fd, shell);
		fd = open("a!", O_RDONLY, 0777);
	}
	return (fd);
}

int	file_rd_exist(t_cmd cmd, int flag1, int flag2)
{
	int	i;

	i = 0;
	while (i < cmd.red_len)
	{
		if (cmd.red[i].flag == flag1 || cmd.red[i].flag == flag2)
			return (1);
		i++;
	}
	return (0);
}

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
	if (fd4 != -1)
		close(fd4);
	return ;
}

void	ft_close_pipes(t_infra *shell, int i, t_cmd cmd)
{
	(void)cmd;
	if (shell->pipe_len > 0)
	{
		if (i == 0)
		{
			close_fds(shell->pfd[0][0], shell->pfd[0][1], -1, -1);
			if (shell->pipe_len > 1)
				close_fds(shell->pfd[1][0], shell->pfd[1][1], -1, -1);
		}
		else if (i == shell->pipe_len)
		{
			close_fds(shell->pfd[shell->pipe_len - 1][0],
				shell->pfd[shell->pipe_len - 1][1], -1, -1);
		}
		else if (shell->pipe_len > 1)
		{
			close_fds(shell->pfd[i - 1][0], shell->pfd[i - 1][1],
				shell->pfd[i][0], shell->pfd[i][1]);
			if ((i + 1) < shell->pipe_len)
				close_fds(shell->pfd[i + 1][0], shell->pfd[i + 1][1], -1, -1);
		}
	}
}

int	parent_process(t_cmd *cmd, int i, t_infra *shell)
{
	if (ft_dup2(shell, cmd, i, 1))
		return (0);
	ft_built_in(cmd[i], shell, cmd);
	return (0);
}
