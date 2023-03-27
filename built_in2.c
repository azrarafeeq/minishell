/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/27 13:15:46 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_cmd(char **str)
{
	int			j;
	long long	num;

	j = -1;
	printf("exit\n");
	if (str[1])
	{
		while (str[1][++j])
		{
			if (str[1][0] == '-')
				j++;
			if (ft_isdigit(str[1][j]) == 0)
				exit_error(str[1], 1);
		}
		num = ft_atoi(str[1]);
		if (num == -1 && ft_strlen(str[1]) != 2)
			exit_error(str[1], 1);
		if (str[2])
			exit_error(str[1], 2);
		else
			exit_stat = ft_atoi(str[1]);
	}
	else
		ft_exit(exit_stat);
}

void	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, MAX_PATH));
	exit_stat = 0;
}

void	ft_echo(char **str)
{
	int		i;

	if (ft_strcmp(str[1], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (ft_strcmp(str[1], "-n") != 0)
		printf("\n");
	exit_stat = 0;
}

int	cmd_is_built_in(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	return (0);
}

void	ft_built_in(t_cmd cmd, t_env **env)
{
	if (ft_strcmp(cmd.main, "cd") == 0)
		ft_cd(cmd.cmd, env);
	else if (ft_strcmp(cmd.main, "export") == 0)
		ft_export(env, cmd.cmd);
	else if (ft_strcmp(cmd.main, "unset") == 0)
		ft_unset(env, cmd.cmd);
	else if (ft_strcmp(cmd.main, "exit") == 0)
		ft_exit_cmd(cmd.cmd);
	else if (ft_strcmp(cmd.main, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd.main, "echo") == 0)
		ft_echo(cmd.cmd);
	else if (ft_strcmp(cmd.main, "pwd") == 0)
		ft_pwd();
}
