/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/17 06:13:22 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_file(char *file, int flag)
{
	//flag according to the struct from parser
	int	fd;

	fd = -1;
	if (flag == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == 3)
		fd = ft_heredoc(file);
	return (fd);
}

void	ft_dup2(t_rdrct **redirect)
{
	//flag according to parser
	int	i;
	int	fd;

	i = 0;
	while (redirect[i])
	{
		fd = open_file(redirect[i]->file, redirect[i]->flag);
		if (redirect[i]->flag != 2) //if not heredoc
			fd_error(fd, redirect[i]->file);
		if (redirect[i]->flag == 0 || redirect[i]->flag == 1)
			dup2(fd, STDIN_FILENO);
		else if (redirect[i]->flag == 2 || redirect[i]->flag == 3)
			dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
		i++;
	}
}

int	file_rd_exist(t_rdrct **rds, int flag1, int flag2)
{
	int	i;

	i = 0;
	while (rds[i])
	{
		if (rds[i] == flag1 || rds[i] == flag2)
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

int	heredoc_exist(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->rds[j])
		{
			if (cmd[i]->rds[j]->flag == 2) //equal to heredoc
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
