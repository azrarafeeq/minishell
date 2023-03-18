/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/17 23:04:55 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	file_rd_exist(t_cmd *cmd, int flag1, int flag2)
{
	int	i;

	i = 0;
	while (i < cmd->rlen)
	{
		if (cmd->rds[i].flag == flag1 || cmd->rds[i].flag == flag2)
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
		while (i < cmd[i]->rlen)
		{
			if (cmd[i]->rds[j].flag == HERE_DOC)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
