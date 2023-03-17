/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/17 06:39:11 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	mt_arg_error(t_cmd *cmd, char **env_arr, t_exec *exec)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd->main);
	while (cmd->main[i] == ' ' && cmd->main[i])
		i++;
	if (cmd->main == NULL || i == len)
	{
		printf("%s: command not found\n", cmd->main);
		free_char_array(env_arr);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
}

void	execve_error(t_exec *exec, t_cmd *cmd)
{
	if (get_path(&(exec->env_list)) == NULL)
	{
		printf("%s: no such file or directory\n", cmd->main);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
	else if (access(cmd->path, F_OK) == -1)
	{
		printf("%s: command not found\n", cmd->main);
		free_exec(exec);
		err_num = 127;
		ft_exit(err_num);
	}
	//else if it doesnt have permission
	else if (access(cmd->path, R_OK) == -1 || access(cmd->path, W_OK) == -1
		|| access(cmd->path, X_OK) == -1)
	{
		printf("%s: Permission denied\n", cmd->main);
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

int	pid_error(int pid)
{
	if (pid == -1)
	{
		//error message
		//err_num = ??
		//exit(err_num);
	}
	return (0);
}
