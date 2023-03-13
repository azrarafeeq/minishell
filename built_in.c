/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:46:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/12 21:33:54 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cd(char **str)
{
	//char			buffer[1024];
	DIR				*dir;

	dir = opendir(str[1]);
	if (dir == NULL)
	{
		printf("cd: %s: No such file or directory\n", str[1]);
		err_num = 1;
		ft_exit(err_num);
	}
	//printf("The current working dir is : %s\n", getcwd(buffer, MAX_PATH));
	chdir(str[1]);
	//printf("Current dir after changing is : %s\n", getcwd(buffer, MAX_PATH))
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
	while (temp)
	{
		printf("%s", temp->var);
		if (temp->value)
			printf("=%s", temp->value);
		printf("\n");
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

	i = 1;
	len = envlst_len(env_list);
	ft_env_pos(env_list);
	temp = *env_list;
	if (str[1])
	{
		env_node = init_env_node(str[1]);
		return (envlst_addback(env_list, env_node));
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
