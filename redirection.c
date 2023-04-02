/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:07:57 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/02 23:42:32 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	red_count(char *str)
{
	int		i;
	int		num;
	char	quote;

	i = 0;
	num = 0;
	quote = 0;
	while (str[i])
	{
		is_quote(str[i], &quote);
		if (!quote && (str[i] == '>' || str[i] == '<'))
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			num++;
		}
		i++;
	}
	return (num);
}

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

void	get_flags(t_cmd *cmds, int *j, int *x, int *y)
{
	cmds->start = *x - 1;
	if (cmds->tmp_cmd[*j][*x + 1] == '>' \
		|| cmds->tmp_cmd[*j][*x + 1] == '<')
	{
		if (cmds->tmp_cmd[*j][*x + 1] == '>')
			cmds[*j].red[*y].flag = APPEND;
		else if (cmds->tmp_cmd[*j][*x + 1] == '<')
		{
			cmds[*j].red[*y].flag = HERE_DOC;
			if(strrchr(cmds->tmp_cmd[*j], '\"'))
				cmds[*j].red[*y].no_expand = 1;
		}
		*x += 2;
	}
	else if (cmds->tmp_cmd[*j][*x] == '>')
	{
		cmds[*j].red[*y].flag = TRUNCATE;
		(*x)++;
	}
	else if (cmds->tmp_cmd[*j][*x] == '<')
	{
		cmds[*j].red[*y].flag = IN_FILE;
		(*x)++;
	}
}
