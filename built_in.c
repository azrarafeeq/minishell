/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 02:46:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/11 15:54:29 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cd(/* parameter */)
{
	//go to the directory
	//opendir
	//readdir
	//closedir
}

void	ft_env(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		printf("%s", temp->var);
		if (temp->value)
			printf("%s", temp->value);
		printf("\n");
		temp = temp->next;
	}
	printf("_=/Users/arafeeq/Desktop/minishell/./minishell\n");
}

void	ft_pwd(void)
{
	char	buffer[1024];

	printf("%s\n", getcwd(buffer, MAX_PATH));
}

void	ft_export(t_env **env_list, char *str)
{
	int		i;
	int		len;
	t_env	*temp;
	t_env	*env_node;

	i = 1;
	len = envlst_len(env_list);
	ft_env_pos(env_list);
	temp = *env_list;
	if (str)
	{
		env_node = init_env_node(str);
		return (envlst_addback(env_list, env_node));
	}
	while (i <= len && temp)
	{
		if (i == temp->pos)
		{
			printf("declare -x %s=%s\n", temp->var, temp->value);
			i++;
			temp = *env_list;
		}
		else
			temp = temp->next;
	}
}

/* void	ft_unset(t_env *env, char *str)
{
	//remove variable from env list
	t_env	*prev;

	prev = env;
	while (env)
	{
		if (ft_strcmp(str, env->var) == 0)
		{
			//what if we want to delete the first node?? 
			//will work but how to return first node
			//put seperate condition?
			prev->next = env->next;
			//free env
			return ;
			//or pointer to the first node??
		}
		prev = env;
		env = env->next;
	}
} */
