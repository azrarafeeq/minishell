/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:52:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/24 14:06:30 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env **env_list)
{
	char	*path;
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PATH") == 0)
		{
			path = temp->value;
			return (path);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	paths_count(char *path)
{
	int	i;
	int	path_count;

	i = 0;
	path_count = 0;
	while (path[i] != '/')
		i++;
	while (path[i])
	{
		if (path[i] == ':' && path[i])
		{
			path_count++;
			while (path[i] != ':' && path[i])
				i++;
		}
		i++;
	}
	return (path_count);
}

char	*append_path_to_array(char *path, int *i)
{
	int		x;
	int		count;
	char	*str;

	x = *i;
	count = 0;
	while (path[x] != ':' && path[x])
	{
		x++;
		count++;
	}
	str = (char *)malloc(sizeof(char) * (count + 1));
	x = 0;
	while (path[*i] != ':' && path[*i])
	{
		str[x] = path[*i];
		(*i)++;
		x++;
	}
	str[x] = '\0';
	return (str);
}

char	**path_array(char *path)
{
	int		i;
	int		j;
	int		p_count;
	char	**path_array;

	i = 0;
	j = 0;
	if (path == NULL)
		return (NULL);
	p_count = paths_count(path);
	path_array = (char **)malloc(sizeof(char *) * (p_count + 1));
	while (path[i] != '/')
		i++;
	while (path[i] && j < p_count)
	{
		if (path[i] == ':')
			i++;
		path_array[j] = append_path_to_array(path, &i);
		j++;
	}
	path_array[j] = NULL;
	return (path_array);
}

char	*check_path(char **path_array, char *command)
{
	int		i;
	char	*path;

	i = -1;
	if (path_array == NULL || !command)
	{
		free(command);
		if (path_array != NULL)
			free_char_array(path_array);
		return (NULL);
	}
	while (path_array[++i])
	{
		path = ft_strjoin(path_array[i], command);
		if (access(path, F_OK) == 0)
		{
			free(command);
			free_char_array(path_array);
			return (path);
		}
		free(path);
	}
	free(command);
	free_char_array(path_array);
	return (NULL);
}
