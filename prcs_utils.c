/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:52:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/28 14:42:53 by arafeeq          ###   ########.fr       */
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

int	parent_process(t_cmd *cmd, int i, t_infra *shell)
{
	if (ft_dup2(shell, cmd, i, 1))
		return (0);
	ft_built_in(cmd[i], &shell->env_list);
	free_char_array(shell->env_arr);
	return (0);
}
