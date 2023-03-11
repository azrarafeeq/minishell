/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/11 21:14:18 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	mt_args_error(t_cmd *cmd, char *c_path, char **env_array)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (cmd->main_cmd[i] == ' ' && cmd->main_cmd[i])
		i++;
	if (cmd->main_cmd == NULL || i == len) //!cmd->main_cmd[0]
	{
		printf("%s: command not found\n", cmd->main_cmd);
		free_char_array(env_array);
		free_cmd(cmd); //create function
		//free other stuff if you missed any
		ft_exit(127);
	}
}

void	execve_error(t_exec *exec, t_cmd *cmd)
{
	char	*path;

	if (get_path(exec->env_list) == NULL)
	{
		printf("%s: no such file or directory\n", cmd->main_cmd);
		//free stuff
		ft_exit(127);
	}
	// else if command doesnt exist
	else if (access(cmd->c_path, F_OK) == -1)
	{
		printf("%s: command not found\n", cmd->main_cmd);
		//free stuff
		ft_exit(127);
	}
	//else if it doesnt have permission
	else if (access(cmd->c_path, R_OK) == -1 || access(cmd->c_path, W_OK) == -1
		|| access(cmd->c_path, X_OK) == -1)
	{
		printf("%s: Permission denied\n", cmd->main_cmd);
		//free stuff
		ft_exit(126);
	}
	//else if it is a directory
	//which flag in access?
}

int	fd_error(int fd, char *file)
{
	//wil have to put condition for heredoc??
	if (fd == -1)
	{
		printf("%s: no such file or directory\n", file);
		//close pipes if any
		return (-1);
	}
	return (0);
}
