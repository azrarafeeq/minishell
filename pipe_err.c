/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:38:09 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/13 18:48:02 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_inbetween(char *line)
{
	int i = 0;
	int j = 0;
	int quote = 0;
	
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (quote == 0)
				quote = line[i];
			else if (!quote)
				quote = 0;
			i++;
			continue ;
		}
		if (line[i] == '|' && !quote)
		{
			j = i + 1;
			while (line[j] == ' ' || line[j] == '\t')
				j++;
			if (line[j] == '|')
				return (0);	
		}
		i++;
	}
	return (1);
}

int	check_pipes(char *line)
{
	int len = ft_strlen(line) - 1;
	if (line[len] == '|' || line[0] == '|')
		return (0);
	if (!pipe_inbetween(line))
		return (0);
	return 1;	
}
