/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 14:04:50 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	mt_arg_error(t_cmd *cmd, char **env_array, t_exec *exec)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (cmd->main_cmd[i] == ' ' && cmd->main_cmd[i])
		i++;
	if (cmd->main_cmd == NULL || i == len)
	{
		printf("%s: command not found\n", cmd->main_cmd);
		free_char_array(env_array);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
}

void	execve_error(t_exec *exec, t_cmd *cmd)
{
	char	*path;

	if (get_path(exec->env_list) == NULL)
	{
		printf("%s: no such file or directory\n", cmd->main_cmd);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
	else if (access(cmd->c_path, F_OK) == -1)
	{
		printf("%s: command not found\n", cmd->main_cmd);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
	//else if it doesnt have permission
	else if (access(cmd->c_path, R_OK) == -1 || access(cmd->c_path, W_OK) == -1
		|| access(cmd->c_path, X_OK) == -1)
	{
		printf("%s: Permission denied\n", cmd->main_cmd);
		free_exec(exec);
		err_num = 126;
		ft_exit(err_num);
	}
	//else if it is a directory
	//which flag in access?
}

int	fd_error(int fd, char *file)
{
	if (fd == -1)
	{
		printf("%s: no such file or directory\n", file);
		//close pipes if any
		err_num = 1;
		ft_exit(err_num);
	}
	return (0);
}
