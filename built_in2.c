/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 20:00:04 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exit(int err_num)
{
	exit(err_num);
}

void	ft_echo(char **str, t_env **env)
{
	int		i;

	if (ft_strcmp(str[1], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (str[++i])
	{
		if (str[i][0] == '$')
			ft_echo_expand(str[i], env);
		else
			printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (ft_strcmp(str[1], "-n") == 0)
		printf("\n");
}

void	ft_echo_expand(char *str, t_env **env)
{
	char	**split;
	t_env	*temp;

	split = ft_split(str, '$');
	temp = *env;
	while (temp)
	{
		if (strcmp(split[1], temp->var) == 0)
		{
			printf("%s", temp->value);
			break ;
		}
		temp = temp->next;
	}
	free_char_array(split);
}

int	cmd_is_built_in(char *str)
{
	int	i;
	char array[8][10] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(str, array[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_built_in(char *cmd, char **args, t_env **env)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args, env);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(env, args);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(env, args);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(env);
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		err_num = 0;
		ft_exit(err_num);
	}
}
