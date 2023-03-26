/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:42:06 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/26 16:13:26 by arafeeq          ###   ########.fr       */
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
		g_exit_stat = 127;
		ft_exit(g_exit_stat);
	}
}

void	execve_error(t_infra *shell, t_cmd *cmd, int i, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	if (get_path(&(shell->env_list)) == NULL)
	{
		printf("%s: No such file or directory\n", cmd[i].main);
		g_exit_stat = 127;
	}
	else if (cmd[i].p == NULL)
	{
		printf("%s: command not found\n", cmd[i].main);
		g_exit_stat = 127;
	}
	else if (access(cmd[i].p, F_OK) == -1)
	{
		printf("%s: No such file or directory\n", cmd[i].main);
		g_exit_stat = 127;
	}
	else if (access(cmd[i].p, X_OK) == -1)
	{
		printf("%s: Permission denied\n", cmd[i].main);
		g_exit_stat = 126;
	}
	else if (access(cmd[i].p, F_OK) == 0)
	{
		printf("%s: is a Directory\n", cmd[i].main);
		g_exit_stat = 126;
	}
	else //remove at the end once everything finised
	{
		printf("output of accces = %d\n", access(cmd[i].p, F_OK));
		printf("cmd[i].p = {%s}\n", cmd[i].p);
		printf("NONE of them\n");
	}
	free_char_array(shell-> e_a);
	free_shell_cmds(shell, cmd);
	ft_exit(g_exit_stat);
}

void	fd_error(char *file)
{
	printf("%s: No such file or directory\n", file);
	//ft_close_pipes(shell, i, cmds[i]);
	g_exit_stat = 1;
}

int	export_error(char **str)
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
			return (1);
		}
		i++;
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
