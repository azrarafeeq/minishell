/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/20 21:15:52 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* void	free_cmd(t_cmd **cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		free_char_array(cmd[j]->cmd);
		free(cmd[j]->main);
		free(cmd[j]->path);
		free(cmd[j]->red);
		free(cmd[j]);
		j++;
	}
	free(cmd);
} */

void	free_shell(t_infra *shell)
{
	//free_cmd(shell->cmds);
	free_char_array(shell->cmds);
	free(shell->env_list);
	free_char_array(shell->path_array);
	free_int_array(shell->pfd, shell->pipe_len);
	free(shell);
}
