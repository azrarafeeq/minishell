/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/04 02:57:50 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_cmd(char **str, t_infra *shell, t_cmd *cmds)
{
	int			j;

	j = -1;
	if (shell->pipe_len == 0)
		printf("exit\n");
	if (str[1])
	{
		if (ft_strcmp(str[1], "-9223372036854775808") == 0)
			ft_exit(0);
		while (str[1][++j])
		{
			if ((str[1][0] == '-' || str[1][0] == '+') && j == 0)
				j++;
			if (ft_isdigit(str[1][j]) == 0)
				exit_error(str[1], 1);
		}
		if (ft_atoi(str[1]) == -1 && ft_strlen(str[1]) != 2)
			exit_error(str[1], 1);
		if (str[2])
			return (exit_error(str[1], 2));
		g_exit_stat = (unsigned char)ft_atoi(str[1]);
	}
	free_shell_cmds_in_child(shell, cmds);
	ft_exit(g_exit_stat);
}

void	ft_pwd(void)
{
	char	buffer[1024];
	char	*pwd;

	pwd = getcwd(buffer, MAX_PATH);
	if (!pwd)
		printf("%s\n", "No such file or directory");
	else
		printf("%s\n", getcwd(buffer, MAX_PATH));
	g_exit_stat = 0;
}

void	ft_echo(char **str)
{
	int		i;

	i = 1;
	g_exit_stat = 0;
	if (!str[1])
		return (printf("\n"), (void)0);
	while (str[i])
	{
		if (ft_strcmp(str[i], "-n") == 0)
			i++;
		else
			break ;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (str[1])
		if (ft_strcmp(str[1], "-n") != 0)
			printf("\n");
}

int	cmd_is_built_in(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "cd") == 0 || !ft_strcmp(str, "/usr/bin/cd"))
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0 || !ft_strcmp(str, "/bin/env"))
		return (1);
	if (ft_strcmp(str, "echo") == 0 || !ft_strcmp(str, "/bin/echo"))
		return (1);
	if (ft_strcmp(str, "pwd") == 0 || !ft_strcmp(str, "/bin/pwd"))
		return (1);
	return (0);
}

void	ft_built_in(t_cmd cmd, t_infra *shell, t_cmd *cmds)
{
	g_exit_stat = 0;
	if (ft_strcmp(cmd.main, "cd") == 0 || !ft_strcmp(cmd.main, "/usr/bin/cd"))
		ft_cd(cmd.cmd, &shell->env_list);
	else if (ft_strcmp(cmd.main, "export") == 0)
		ft_export(&shell->env_list, cmd.cmd);
	else if (ft_strcmp(cmd.main, "unset") == 0)
		ft_unset(&shell->env_list, cmd.cmd);
	else if (ft_strcmp(cmd.main, "exit") == 0)
		ft_exit_cmd(cmd.cmd, shell, cmds);
	else if (!ft_strcmp(cmd.main, "env") || !ft_strcmp(cmd.main, "/bin/env"))
		ft_env(&shell->env_list);
	else if (!ft_strcmp(cmd.main, "echo") || !ft_strcmp(cmd.main, "/bin/echo"))
		ft_echo(cmd.cmd);
	else if (!ft_strcmp(cmd.main, "pwd") || !ft_strcmp(cmd.main, "/bin/pwd"))
		ft_pwd();
}
