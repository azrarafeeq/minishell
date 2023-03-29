/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:55:35 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/29 04:12:29 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err(t_infra *shell)
{
	if (!right_quotes(shell->trim_rd) || !check_redirect(shell->trim_rd) \
		|| !check_pipes(shell->trim_rd))
		return ((g_exit_stat = 258), (printf(SYN_ERR), 0));
	return (1);
}

int	pipe_inbetween(char *line, int i, int j, int quote)
{
	i = 0;
	j = 0;
	quote = 0;
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
	int	len;
	int	i;
	int	j;
	int	quote;

	len = ft_strlen(line) - 1;
	if (line[len] == '|' || line[0] == '|')
		return (0);
	if (!pipe_inbetween(line, i, j, quote))
		return (0);
	return (1);
}

void free_trim(char **trim)
{
	if(*trim)
		free(*trim);
	*trim = NULL;	
}
