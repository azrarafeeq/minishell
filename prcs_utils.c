/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 20:11:49 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_file(char *file, char *redirection)
{
	int	fd;

	if (ft_strcmp(redirection, "<") == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (ft_strcmp(redirection, ">") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(redirection, ">>") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (ft_strcmp(redirection, "<<") == 0)
		fd = ft_heredoc(file);
	return (fd);
}

void	ft_dup2(t_rdrct **redirect, int flag)
{
	int	i;
	int	fd;

	while (redirect[i])
	{
		fd = open_file(redirect[i]->file, redirect[i]->sign);
		if (ft_strcmp(redirect[i]->sign, "<<"))
			fd_error(fd, redirect[i]->file);
		if (flag == 0)
			dup2(fd, STDIN_FILENO);
		else if (flag == 1)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
}

int	file_rd_exist(t_rdrct **rds)
{
	if (*rds != NULL)
		return (1);
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
		while (cmd[i]->in_rds[j])
		{
			if (ft_strcmp(cmd[i]->in_rds[j]->sign, "<<") == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
