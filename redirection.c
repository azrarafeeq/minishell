/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:07:57 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/25 16:56:28 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *str, int *i, int flag)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		(*i)++;
		if ((str[*i] == '<' && str[*i - 1] == '<')
			|| (str[*i] == '>' && str[*i - 1] == '>'))
			(*i)++;
		while (str[*i] == ' ' || str[*i] == '\t')
			(*i)++;
		if ((str[*i] == '>' || str[*i] == '<') && (!flag))
			return (FALSE);
		if ((str[*i] == '\0' || str[*i] == '|') && (!flag))
			return (FALSE);
	}
	else
		(*i)++;
	return (TRUE);
}

int	check_redirect(char *str)
{
	int	i;
	int	len;
	int	flag;

	len = ft_strlen(str) - 1;
	flag = FALSE;
	if (str[len] == '>' || str[len] == '<')
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!flag)
				flag = str[i];
			else if (flag == str[i])
				flag = FALSE;
		}
		if (!is_redirect(str, &i, flag))
			return (FALSE);
	}
	return (TRUE);
}
