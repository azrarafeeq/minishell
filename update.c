/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:58:47 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/20 14:54:24 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env **env_list)
{
	char	buf[1024];
	char	*cur_pwd;
	t_env	*temp;

	cur_pwd = NULL;
	temp = *env_list;
	while (temp)
	{
		if (ft_strcmp(temp->var, "PWD") == 0)
		{
			cur_pwd = malloc(sizeof(char) * (ft_strlen(temp->value) + 1));
			ft_strcpy(cur_pwd, temp->value);
			free(temp->value);
			temp->value = malloc(sizeof(char)
					* (ft_strlen(getcwd(buf, MAX_PATH)) + 1));
			ft_strcpy(temp->value, getcwd(buf, MAX_PATH));
			break ;
		}
		temp = temp->next;
	}
	update_oldpwd(env_list, cur_pwd);
	free(cur_pwd);
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
			temp->value = malloc(sizeof(char) * (ft_strlen(str) + 1));
			ft_strcpy(temp->value, split[1]);
			break ;
		}
		temp = temp->next;
	}
	free_char_array(split);
}
