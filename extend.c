/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:59:31 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/02 21:20:12 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes(char *str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = (char *) malloc(len + 3);
	if (!new_str)
		return (printf("Memory allocation error\n"), NULL);
	new_str[0] = '"';
	ft_strcpy(&new_str[1], str);
	new_str[len + 1] = '"';
	new_str[len + 2] = '\0';
	return (new_str);
}

int	get_stat(char **fifty_cent, t_infra *sh, char *expandable)
{
	sh->i++;
	if ((*fifty_cent)[sh->i] == '?' && (*fifty_cent)[sh->i - 1] == '$')
	{
		expandable = ft_itoa(g_exit_stat);
		*fifty_cent = modify_cmd(*fifty_cent, sh->i - 1, 2, expandable);
		sh->i += ft_strlen(expandable) - 2;
		free(expandable);
		return (1);
	}
	return (0);
}

void	update_cmd(char **dol, char *expanded, t_infra *sh)
{
	*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, expanded);
	sh->i += ft_strlen(expanded) - sh->len - 1;
}

int	is_alpha_num(char *dol, t_infra *sh)
{
	if (!ft_isalpha(dol[sh->i]))
		return (1);
	sh->len = 0;
	while (ft_isalnum(dol[sh->i]))
	{
		sh->len++;
		sh->i++;
	}
	return (0);
}

void	get_hundred_cent(char **fifty_cent, t_infra *sh, int flag)
{
	char	*expandable;
	char	*dol;

	sh->len = 0;
	sh->i = 0;
	dol = *fifty_cent;
	while (sh->i < ft_strlen((*fifty_cent)))
	{
		if (flag)
			seperate_quote((*fifty_cent)[sh->i], sh);
		if (!(*fifty_cent)[sh->i])
			return ;
		if ((*fifty_cent)[sh->i] == '$' && !sh->single)
		{
			if (get_stat(fifty_cent, sh, expandable))
				continue ;
			if (is_alpha_num((*fifty_cent), sh))
				continue ;
			expandable = ft_substr((*fifty_cent), sh->i - sh->len, sh->len);
			if (expande_it(fifty_cent, &expandable, sh))
				continue ;
		}
		sh->i++;
	}
}
