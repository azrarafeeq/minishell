/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:46:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/31 21:02:42 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **str, t_env **env_list)
{
	DIR				*dir;

	if (str[1] == NULL || str[1][0] == '\0')
	{
		ft_putstr_fd("cd: No directory specified\n", 2);
		g_exit_stat = 1;
		return ;
	}
	dir = opendir(str[1]);
	if (dir == NULL)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_stat = 1;
		return ;
	}
	chdir(str[1]);
	update_pwd(env_list);
}

void	ft_env(t_env **env_list)
{
	t_env	*temp;

	if (get_path(env_list) == NULL)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		g_exit_stat = 127;
		return ;
	}
	temp = *env_list;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->var, temp->value);
		temp = temp->next;
	}
	printf("_=/Users/arafeeq/Desktop/minishell/./minishell\n");
	g_exit_stat = 0;
}

void	ft_export(t_env **env_list, char **str)
{
	int		i;
	t_env	*env_node;

	i = 0;
	ft_env_pos(env_list);
	while (str[++i])
	{
		if (export_unset_error(str[i], 1) == 0)
		{
			if (var_exists(env_list, str[i]))
			{
				if (ft_strchr(str[i], '='))
					update_var(env_list, str[i]);
			}
			else
			{
				env_node = init_env_node(str[i]);
				envlst_addback(env_list, env_node);
			}
		}
	}
	if (!str[1])
		print_export(env_list);
}

void	print_export(t_env **env_list)
{
	int		i;
	int		len;
	t_env	*temp;

	i = 1;
	temp = *env_list;
	len = envlst_len(env_list);
	while (i <= len && temp)
	{
		if (i == temp->pos)
		{
			printf("declare -x %s", temp->var);
			if (temp->value != NULL)
				printf("=\"%s\"", temp->value);
			printf("\n");
			i++;
			temp = *env_list;
		}
		else
			temp = temp->next;
	}
}

void	ft_unset(t_env **env, char **str)
{
	t_env	*temp;
	t_env	*prev;
	int		i;

	temp = *env;
	prev = *env;
	i = 1;
	while (str[i])
	{
		if (export_unset_error(str[i], 0) == 0)
		{
			while (temp)
			{
				if (ft_strcmp(str[i], temp->var) == 0)
				{
					delete_node(env, temp, prev);
					break ;
				}
				prev = temp;
				temp = temp->next;
			}
			temp = *env;
		}
		i++;
	}
}
