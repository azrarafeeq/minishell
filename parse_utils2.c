/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:57:10 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/26 15:07:04 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*modify_cmd(char *dol, int start, int len, char *extended)
{
	char	*new_str;
	int		i;
	int		j;

	if (!dol || start + len > (int)ft_strlen(dol))
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(dol) + ft_strlen(extended) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start)
		new_str[j++] = dol[i++];
	while (*extended)
		new_str[j++] = *extended++;
	while (dol[i + len])
		new_str[j++] = dol[i++ + len];
	new_str[j] = '\0';
	return (new_str);
}

void	get_cmd(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i < start || i >= len)
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

void seperate_quote(char cur, t_infra *sh)
{
	if (cur == '\"')
	{
			if (!sh->paired)
				sh->paired = cur;
			else if (sh->paired)
				sh->paired = 0;
	}
	if (cur == '\'' && !sh->paired)
	{
			if (!sh->single)
				sh->single = cur;
			else if (sh->single)
				sh->single = 0;
	}
}