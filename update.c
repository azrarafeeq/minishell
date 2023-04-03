/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:58:47 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/04 01:52:45 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env **env_list, char *cur_pwd, char *pwd)
{
	char	buf[1024];
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
		{
			cur_pwd = ft_calloc(sizeof(char), (ft_strlen(temp->value) + 1));
			ft_strcpy(cur_pwd, temp->value);
			free(temp->value);
			pwd = getcwd(buf, MAX_PATH);
			if (pwd)
				temp->value = ft_strdup(pwd);
			else
				temp->value = NULL;
			break ;
		}
		temp = temp->next;
	}
	if (cur_pwd != NULL || cur_pwd[0] != '\0')
	{
		update_oldpwd(env_list, cur_pwd);
		free(cur_pwd);
	}
}

void	update_oldpwd(t_env **env_list, char *cur_pwd)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->var, "OLDPWD") == 0)
		{
			free(temp->value);
			temp->value = malloc(sizeof(char) * (ft_strlen(cur_pwd) + 1));
			ft_strcpy(temp->value, cur_pwd);
			break ;
		}
		temp = temp->next;
	}
}

void	update_var(t_env **env_list, char *str)
{
	t_env	*temp;
	char	**split;

	temp = *env_list;
	split = ft_split(str, '=');
	while (temp)
	{
		if (ft_strcmp(temp->var, split[0]) == 0)
		{
			free(temp->value);
			if (split[1] != NULL)
			{
				temp->value = malloc(sizeof(char) * (ft_strlen(str) + 1));
				ft_strcpy(temp->value, split[1]);
				break ;
			}
			else
				temp->value = ft_strdup("");
		}
		temp = temp->next;
	}
	free_char_array(split);
}
