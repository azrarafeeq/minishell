/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:38:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/02 19:22:56 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_env **envlist)
{
	char	*join;
	int		len;
	char	**array;
	int		i;
	t_env	*t;

	i = 0;
	t = *envlist;
	len = envlst_len(envlist);
	array = malloc(sizeof(char *) * (len + 1));
	while (t)
	{
		join = ft_strjoin(t->var, "=");
		array[i] = ft_strjoin(join, t->value);
		free(join);
		i++;
		t = t->next;
	}
	array[i] = NULL;
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

int	var_exist(t_env **env_list, char *str)
{
	char	**split;
	t_env	*temp;

	temp = *env_list;
	if (ft_strchr(str, '='))
	{
		split = ft_split(str, '=');
		while (temp)
		{
			if (ft_strcmp(split[0], temp->var) == 0)
				return (free_char_array(split), 1);
			temp = temp->next;
		}
		free_char_array(split);
	}
	else
	{
		while (temp)
		{
			if (ft_strcmp(str, temp->var) == 0)
				return (1);
			temp = temp->next;
		}
	}
	return (0);
}

void	ft_exit(int g_exit_stat)
{
	exit(g_exit_stat);
}
