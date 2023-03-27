/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/28 02:26:30 by ahassan          ###   ########.fr       */
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
			i++;
		}
		free(array);
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

/* void	free_cmds(char **cmds)
{
	char	**tmp;

	tmp = cmds;
	while (*cmds)
		free(*cmds++);
	free(tmp);
} */

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

	j = 0;
	while (j < (shell->pipe_len + 1))
	{
		free(cmds[j].main);
		//free_char_array(cmds[j].tmp_cmd);
		//free_char_array(cmds[j].cmd);
		//free(cmds[j].p);
		//free(cmds[j].red->file);
		//free(cmds[j].red);
		j++;
	}
	free(cmds);
	free(shell->rd);
	//free(shell->trim_rd);
	// free_char_array(shell->cmds);
	free_char_array(shell->env_arr);
	free_env_list(&shell->env_list);
	free_int_array(shell->pfd, shell->pipe_len);
	//free(shell);
}

void	free_structs(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->cmd_len)
	{
		if(cmd[i].red_len)
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
