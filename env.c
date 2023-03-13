/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:30:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 20:00:04 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_env_pos(t_env **env_list)
{
	int		i;
	int		j;
	t_env	*t;
	t_env	*t2;

	t = *env_list;
	t2 = *env_list;
	while (t2)
	{
		i = 1;
		while (t)
		{
			j = 0;
			if (t2->var[j] >= t->var[j])
			{
				if (t2->var[j] == t->var[j])
					while (t2->var[j] == t->var[j] && t2->var[j] && t->var[j])
						j++;
				if (t2->var[j] > t->var[j])
					i++;
			}
			t = t->next;
		}
		t = *env_list;
		t2->pos = i;
		t2 = t2->next;
	}
}

int	envlst_len(t_env **env_list)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = *env_list;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	envlst_addback(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!*lst || !new)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_env	*init_env_node(char *str)
{
	t_env	*env_node;
	char	**split;

	env_node = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	env_node->whole = malloc(sizeof(char) * ft_strlen(str));
	ft_strcpy(env_node->whole, str);
	env_node->var = malloc(sizeof(char) * ft_strlen(split[0]));
	ft_strcpy(env_node->var, split[0]);
	if (split[1])
	{
		env_node->value = malloc(sizeof(char) * ft_strlen(split[1]));
		ft_strcpy(env_node->value, split[1]);
	}
	else
		env_node->value = NULL;
	env_node->next = NULL;
	free_char_array(split);
	return (env_node);
}

void	ft_envp(char **envp, t_env **env_list)
{
	int		i;
	t_env	*env_node;

	i = 0;
	while (envp[i + 1])
	{
		env_node = init_env_node(envp[i]);
		envlst_addback(env_list, env_node);
		i++;
	}
}
