/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/22 20:35:50 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_cmd(char **str)
{
	int			j;
	long long	num;

	j = -1;
	printf("exit\n");
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
	j = -1;
	while (str[++j])
		j++;
	if (j > 2)
		exit_error(str[1], 2);
	else
	{
		exit_stat = ft_atoi(str[1]);
		ft_exit(exit_stat);
	}
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
	if (ft_strcmp(str[1], "-n") == 0)
		printf("\n");
	exit_stat = 0;
	ft_exit(exit_stat);
}

int	cmd_is_built_in(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		if (ft_strcmp(str, "cd") == 0)
			return (1);
		if (ft_strcmp(str, "export") == 0)
			return (1);
		if (ft_strcmp(str, "unset") == 0)
			return (1);
		if (ft_strcmp(str, "exit") == 0)
			return (1);
	}
	else if (flag == 2)
	{
		if (ft_strcmp(str, "echo") == 0)
			return (1);
		if (ft_strcmp(str, "pwd") == 0)
			return (1);
		if (ft_strcmp(str, "env") == 0)
			return (1);
	}
	return (0);
}

void	ft_built_in(char *cmd, char **args, t_env **env, int flag)
{
	if (flag == 1)
	{
		if (ft_strcmp(cmd, "cd") == 0)
			ft_cd(args, env);
		else if (ft_strcmp(cmd, "export") == 0)
			ft_export(env, args);
		else if (ft_strcmp(cmd, "unset") == 0)
			ft_unset(env, args);
		else if (ft_strcmp(cmd, "exit") == 0)
			ft_exit_cmd(args);
	}
	else if (flag == 2)
	{
		if (ft_strcmp(cmd, "echo") == 0)
			ft_echo(args);
		else if (ft_strcmp(cmd, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd, "env") == 0)
			ft_env(env);
	}
}
