/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/30 21:34:20 by arafeeq          ###   ########.fr       */
=======
/*   Updated: 2023/03/30 21:30:53 by ahassan          ###   ########.fr       */
>>>>>>> aa9a0d05864ef823f061b3e5583b5a3d924b7324
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			if (array[i])
				free(array[i]);
			array[i] = NULL;	
			i++;
		}
		free(array);
		array = NULL;
	}
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

void	free_env_list(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (*env_list != NULL)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp->var);
		free(temp->value);
		free(temp);
	}
	free (*env_list);
}

void	free_shell_cmds_in_child(t_infra *shell, t_cmd *cmds)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (j < (shell->pipe_len + 1))
	{
		if (cmds[j].cmd != NULL)
			free_char_array(cmds[j].cmd);
		if (cmds[j].red_len > 0)
		{
			while (++i < cmds[j].red_len)
				free(cmds[j].red[i].file);
			if (cmds[j].red)
				free(cmds[j].red);
		}
		j++;
	}
	if (cmds)
		free(cmds);
	free(shell->rd);
	free_char_array(shell->env_arr);
	free_env_list(&shell->env_list);
	if (shell->pfd)
		free_int_array(shell->pfd, shell->pipe_len);
}

void	free_structs(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->cmd_cnt)
	{
		if (cmd[i].red_len)
		{
			j = -1;
			while (++j < cmd[i].red_len)
				free(cmd[i].red[j].file);
			free(cmd[i].red);
		}
		free_char_array(cmd[i].cmd);
		i++;
	}
	free(cmd);
}
