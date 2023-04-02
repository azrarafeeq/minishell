/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/02 15:41:25 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mt_arg_error(t_infra *shell, t_cmd *cmds, int j)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmds[j].main);
	while (cmds[j].main[i] == ' ' && cmds[j].main[i])
		i++;
	if (cmds[j].main == NULL || i == len)
	{
		printf("path = %s\n", cmds[j].p);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_stat = 127;
		free(cmds[j].p);
		free_shell_cmds_in_child(shell, cmds);
	}
}

void	execve_error(t_infra *shell, t_cmd *cmd, int i)
{
	ft_putstr_fd(cmd[i].main, 2);
	if (get_path(&(shell->env_list)) == NULL)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (cmd[i].p == NULL)
		ft_putstr_fd(": command not found\n", 2);
	else if (access(cmd[i].p, F_OK) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (access(cmd[i].p, X_OK) == -1)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (access(cmd[i].p, F_OK) == 0)
		ft_putstr_fd(": is a Directory\n", 2);
	if (get_path(&(shell->env_list)) == NULL || cmd[i].p == NULL
		|| access(cmd[i].p, F_OK) == -1)
		g_exit_stat = 127;
	else if (access(cmd[i].p, X_OK) == -1 || access(cmd[i].p, F_OK) == 0)
		g_exit_stat = 126;
	if (ft_strchr(cmd[i].main, '/') == 0)
		free(cmd[i].p);
}

int	fd_error(char *file, t_infra *shell, t_cmd *cmds, int i)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_stat = 1;
	ft_close_pipes(shell, i, cmds[i]);
	return (0);
}

int	export_unset_error(char *str, int flag)
{
	int	i;
	int	err;

	i = -1;
	err = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
		{
			err = 1;
			break ;
		}
	}
	if (!(ft_isalpha(str[0]) || str[0] == '_') || err)
	{
		if (flag)
			write(2, "export: '", 9);
		else
			write(2, "unset: '", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 27);
		g_exit_stat = 1;
		return (1);
	}
	return (0);
}

void	exit_error(char *str, int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_stat = 255;
		ft_exit(g_exit_stat);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exit_stat = 1;
	}
}
