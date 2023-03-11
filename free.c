/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:17:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/11 21:07:16 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	free_intarray(int **int_array, int len)
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

void	free_redirection(t_rdrct **rdrct)
{
	int	i;

	i = 0;
	while (rdrct[i])
	{
		free(rdrct[i]);
		i++;
	}
	free(rdrct);
}

void	free_cmd(t_cmd *cmd)
{
	free_char_array(cmd->cmd_and_args);
	free(cmd->main_cmd);
	free(cmd->c_path);
	free_redirection(cmd->in_rds);
	free_redirection(cmd->out_rds);
	free(cmd);
}
