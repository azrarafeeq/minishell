/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:30:38 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/04 01:18:13 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_env_pos2(t2, t, &i, &j);
			t = t->next;
		}
		t = *env_list;
		t2->pos = i;
		t2 = t2->next;
	}
}

void	ft_env_pos2(t_env *t2, t_env *t, int *i, int *j)
{
	if (t2->var[*j] >= t->var[*j])
	{
		if (t2->var[*j] == t->var[*j])
			while (t2->var[*j] == t->var[*j] && t2->var[*j] && t->var[*j])
				(*j)++;
		if (t2->var[*j] > t->var[*j])
			(*i)++;
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

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env	*init_env_node(char *str)
{
	t_env	*env_node;
	char	**split;
	int		len;

	env_node = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	env_node->var = ft_calloc(sizeof(char), ft_strlen(split[0]) + 1);
	ft_strcpy(env_node->var, split[0]);
	len = ft_strlen(str) - (ft_strlen(split[0]) + 1);
	if (ft_strchr(str, '='))
	{
		if (!split[1])
			env_node->value = ft_calloc(sizeof(char), 1);
		else
			env_node->value = ft_substr(str, (ft_strlen(split[0]) + 1), len);
	}
	else
		env_node->value = NULL;
	env_node->next = NULL;
	free_char_array(split);
	return (env_node);
}
