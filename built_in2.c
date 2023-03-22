/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/22 18:15:47 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_cmd(char **str)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	j = -1;
	printf("exit\n");
	while (str[1][++j])
		if (ft_isdigit(str[1][j]) == 0)
			exit_error(str[1], 1);
	num = ft_atoi(str[i]);
	if (num == -1) //error return from atoi
		exit_error(str[1], 1);
	while (str[i])
		i++;
	if (i > 2)
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
}

int	cmd_is_built_in(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

void	ft_built_in(char *cmd, char **args, t_env **env)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(args, env);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(env, args);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(env, args);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit_cmd(args);
}
