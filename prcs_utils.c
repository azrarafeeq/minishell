/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/25 17:44:25 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	heredoc_exist(t_infra *shell, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < (shell->pipe_len + 1))
	{
		j = 0;
		while (j < cmd[i].red_len)
		{
			if (cmd[i].red[j].flag == HERE_DOC)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	process2(t_infra *shell, t_cmd *cmd, int i, t_env **env_list)
{
	if (ft_strrchr(cmd[i].main, '/'))
		cmd[i].p = cmd[i].main;
	else
		cmd[i].p = check_path(path_array(get_path(env_list)),
				ft_strjoin("/", cmd[i].main));
	ft_close_pipes(shell, i, cmd[i]);
}
