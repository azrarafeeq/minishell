/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:46:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/21 22:47:06 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **str, t_env **env_list)
{
	DIR				*dir;

	if (str[1] == NULL || str[1][0] == '\0')
		ft_exit(1);
	dir = opendir(str[1]);
	if (dir == NULL)
	{
		printf("cd: %s: No such file or directory\n", str[1]);
		exit_stat = 1;
		ft_exit(exit_stat);
	}
	chdir(str[1]);
	update_pwd(env_list);
}

void	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, MAX_PATH));
}

void	ft_env(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (temp->next)
	{
		if (temp->value != NULL)
			printf("%s=%s\n", temp->var, temp->value);
		temp = temp->next;
	}
	printf("_=/Users/arafeeq/Desktop/minishell/./minishell\n");
}

void	ft_export(t_env **env_list, char **str)
{
	int		i;
	int		len;
	t_env	*temp;
	t_env	*env_node;

	export_error(str);
	i = 1;
	len = envlst_len(env_list);
	ft_env_pos(env_list);
	temp = *env_list;
	if (str[i])
	{
		if (var_exists(env_list, str[i]))
		{
			if (ft_strchr(str[i], '='))
				return (update_var(env_list, str[i]));
		}
		else
		{
			env_node = init_env_node(str[1]);
			envlst_addback(env_list, env_node);
			return ;
		}
	}
	while (i <= len && temp)
	{
		if (i == temp->pos)
		{
			printf("declare -x %s=\"%s\"\n", temp->var, temp->value);
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

	temp = *env;
	prev = *env;
	while (temp)
	{
		if (ft_strcmp(str[1], temp->var) == 0)
		{
			if (temp == *env)
				(*env) = (*env)->next;
			else if (temp->next == NULL)
				prev->next = NULL;
			else
				prev->next = temp->next;
			free(temp);
			temp = NULL;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
