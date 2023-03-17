/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:38:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/14 16:46:24 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**list_to_array(t_env **envlist)
{
	int		list_len;
	char	**array;
	int		i;
	t_env	*t;

	list_len = envlst_len(envlist);
	array = malloc(sizeof(char *) * (list_len + 1));
	i = 0;
	t = *envlist;
	while (t)
	{
		array[i] = malloc(sizeof(char) * (ft_strlen(t->whole)));
		ft_strcpy(array[i], t->whole);
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

int	rds_count(char **split)
{
	int	i;
	int	count;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '<' || split[i][0] == '>')
			count++;
		i++;
	}
	return (count);
}

int	cmds_count(char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (split[i])
	{
		if (split[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}
