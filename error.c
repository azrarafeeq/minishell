/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/18 21:54:21 by arafeeq          ###   ########.fr       */
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
		exit_stat = 127;
		ft_exit(exit_stat);
	}
}

void	execve_error(t_exec *exec, t_cmd *cmd)
{
	if (get_path(&(exec->env_list)) == NULL) //unset path
	{
		printf("%s: no such file or directory\n", cmd->main);
		free_exec(exec);
		exit_stat = 127;
	}
	else if (cmd->path == NULL) //wrong command
	{
		printf("%s: command not found\n", cmd->main);
		free_exec(exec);
		exit_stat = 127;
	}
	else if (access(cmd->path, X_OK) == -1) //doesn't have excution permissions
	{
		printf("%s: Permission denied\n", cmd->main);
		free_exec(exec);
		exit_stat = 126;
	}
	else if (access(cmd->path, F_OK) == -1) //is a directory
	{
		printf("%s: is a Directory\n", cmd->main);
		free_exec(exec);
		exit_stat = 126;
	}
	ft_exit(exit_stat);
}

int	fd_error(int fd, char *file)
{
	if (fd == -1)
	{
		printf("%s: no such file or directory\n", file);
		//close pipes if any
		exit_stat = 1;
		ft_exit(exit_stat);
	}
	return (0);
}

int	pid_error(int pid)
{
	if (pid == -1)
	{
		//error message
		//exit_stat = ??
		//exit(exit_stat);
	}
	return (0);
}

void	export_error(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!(ft_isalpha(str[0]) || str[0] == '_'))
		{
			write(2, "export: '", 9);
			write(2, str[1], ft_strlen(str[1]));
			write(2, "': not a valid identifier\n", 27);
			exit_stat = 1;
			ft_exit(1);
		}
		i++;
	}
}

void	exit_error(char *str, int flag)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (flag == 1)
	{
		exit_stat = 255; // or accordingly
		ft_exit(exit_stat);
	}
	else if (flag == 2)
		exit_stat = 1;
}
