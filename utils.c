/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:38:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/18 18:16:38 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**list_to_array(t_env **envlist)
{
	char	*join;
	char	**array;
	int		i;
	t_env	*t;

	i = 0;
	t = *envlist;
	while (t)
	{
		join = ft_strjoin(t->var, "=");
		array[i] = ft_strjoin(join, t->value);
		i++;
		t = t->next;
	}
	return (array);
}

char	*ft_getenv(t_env **env, char *str)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->var, str) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

int	var_exists(t_env **env_list, char *str)
{
	char	**split;
	t_env	*temp;

	temp = *env_list;
	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '=');
		while (temp)
		{
			if (ft_strcmp(split[0], temp->value) == 0)
				return (1);
			temp = temp->next;
		}
	}
	else
	{
		while (temp)
		{
			if (ft_strcmp(split[0], temp->value) == 0)
				return (1);
			temp = temp->next;
		}
	}
}
