/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/23 17:25:26 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mt_arg_error(t_cmd cmd, char **env_arr, t_infra *shell, t_cmd *cmds)
{
	int	i;
	int	len;

	i = 0;
	(void)shell;
	(void)cmds;
	len = ft_strlen(cmd.main);
	while (cmd.main[i] == ' ' && cmd.main[i])
		i++;
	if (cmd.main == NULL || i == len)
	{
		printf("%s: command not found\n", cmd.main);
		free_char_array(env_arr);
		//free_shell_cmds(shell, cmds);
		exit_stat = 127;
		ft_exit(exit_stat);
	}
}

void	execve_error(t_infra *shell, t_cmd *cmd, int i)
{
	if (get_path(&(shell->env_list)) == NULL)
	{
		printf("%s: no such file or directory\n", cmd[i].main);
		exit_stat = 127;
	}
	if (cmd[i].p == NULL)
	{
		printf("%s: command not found\n", cmd[i].main);
		exit_stat = 127;
	}
	else if (access(cmd[i].p, X_OK) == -1)
	{
		printf("%s: Permission denied\n", cmd[i].main);
		exit_stat = 126;
	}
	else if (access(cmd[i].p, F_OK) == -1)
	{
		printf("%s: is a Directory\n", cmd[i].main);
		exit_stat = 126;
	}
	//free_shell_cmds(shell, cmds);
	ft_exit(exit_stat);
}

int	fd_error(int fd, char *file, t_infra *shell, t_cmd *cmds)
{
	(void)cmds;
	if (fd == -1)
	{
		printf("%s: no such file or directory\n", file);
		if (shell->pfd)
		//close pipes if any
		//free_shell_cmds(shell, cmds);
		exit_stat = 1;
		ft_exit(exit_stat);
	}
	return (0);
}

void	export_error(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (!(ft_isalpha(str[i][0]) || str[i][0] == '_'))
		{
			write(2, "export: '", 9);
			write(2, str[i], ft_strlen(str[i]));
			write(2, "': not a valid identifier\n", 27);
			exit_stat = 1;
		}
		i++;
	}
}

void	exit_error(char *str, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_stat = 255;
		ft_exit(exit_stat);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": too many arguments\n", 2);
		exit_stat = 1;
	}
}
