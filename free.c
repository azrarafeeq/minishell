/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 20:00:04 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int **int_array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(int_array[i]);
		i++;
	}
	free(int_array);
}

void	free_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cmd[j])
	{
		free_char_array(cmd[j]->cmd_and_args);
		free(cmd[j]->main_cmd);
		free(cmd[j]->c_path);
		while (cmd[j]->in_rds[++i])
			free(cmd[j]->in_rds[i]);
		free(cmd[j]->in_rds);
		i = -1;
		while (cmd[j]->out_rds[++i])
			free(cmd[j]->out_rds[i]);
		free(cmd[j]->out_rds);
		free(cmd[j]);
		j++;
	}
	free(cmd);
}

void	free_exec(t_exec *exec)
{
	free_cmd(exec->cmds);
	free(exec->env_list);
	free_char_array(exec->path_array);
	free_int_array(exec->pfd, exec->cmd_amt - 1);
	free(exec);
}
