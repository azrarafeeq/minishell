/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/27 20:21:25 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mt_arg_error(t_infra *shell, t_cmd *cmds, int j)
{
	int	i;
	int	len;

	i = 0;
	(void)shell;
	(void)cmds;
	len = ft_strlen(cmds[j].main);
	while (cmds[i].main[i] == ' ' && cmds[i].main[i])
		i++;
	if (cmds[i].main == NULL || i == len)
	{
		ft_putstr_fd(": command not found\n", 2);
		g_exit_stat = 127;
		free(cmds[i].p);
		free_char_array(shell->env_arr);
		free_shell_cmds_in_child(shell, cmds);
		g_exit_stat = 127;
		ft_exit(g_exit_stat);
	}
}

void	execve_error(t_infra *shell, t_cmd *cmd, int i, char **env_arr)
{
	(void)env_arr;
	ft_putstr_fd(cmd[i].main, 2);
	if (get_path(&(shell->env_list)) == NULL)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_stat = 127;
	}
	else if (cmd[i].p == NULL)
	{
		ft_putstr_fd(": command not found\n", 2);
		g_exit_stat = 127;
	}
	else if (access(cmd[i].p, F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_stat = 127;
	}
	else if (access(cmd[i].p, X_OK) == -1)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_stat = 126;
	}
	else if (access(cmd[i].p, F_OK) == 0)
	{
		ft_putstr_fd(": is a Directory\n", 2);
		g_exit_stat = 126;
	}
	//free_char_array(env_arr);
	free(cmd[i].p);
	free_shell_cmds_in_child(shell, cmd);
	ft_exit(g_exit_stat);
}

int	fd_error(char *file, t_infra *shell, t_cmd *cmds, int i)
{
	(void)cmds;
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_stat = 1;
	ft_close_pipes(shell, i, cmds[i]);
	if (i > 0)
		free_shell_cmds_in_child(shell, cmds);
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
			g_exit_stat = 1;
			//return or exit based on parent or child
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
		g_exit_stat = 255;
		//return or exit based on child or parent
		ft_exit(g_exit_stat);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exit_stat = 1;
	}
}
