/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:30 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/12 14:35:05 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_exit(int err_num)
{
	exit(err_num);
}

void	ft_echo(char **str, int flag, t_env **env)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '$')
			ft_echo_expand(str[i], env);
		else
			printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (flag == 0)
		printf("\n", str);
}

void	ft_echo_expand(char *str, t_env **env)
{
	char	**split;
	t_env	*temp;

	split = ft_split(str, '$');
	temp = *env;
	while (temp)
	{
		if (strcmp(split[1], temp->var) == 0)
		{
			printf("%s", temp->value);
			break ;
		}
		temp = temp->next;
	}
	free_char_array(split);
}
