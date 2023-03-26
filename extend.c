/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:59:31 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/27 03:24:15 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *add_quotes(char *str)
{
    int len = ft_strlen(str);
    char *new_str = (char*) malloc(len + 3);
    if (!new_str)
    	return (printf("Memory allocation error\n"), NULL);
    new_str[0] = '"';
    ft_strcpy(&new_str[1], str);
    new_str[len + 1] = '"';
    new_str[len + 2] = '\0';
    return new_str;
}

void update_cmd(char **dol, char *expanded, t_infra *sh)
{
	if (!sh->paired)
	{
		char *quoted = add_quotes(expanded);
		*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, quoted);
		sh->i += ft_strlen(expanded) - sh->len - 1;
		free(quoted);
	}
	else
	{
		*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, expanded);
		sh->i += ft_strlen(expanded) - sh->len - 1;
	}
}

int	expande_it(char **dol, char **expandable, t_infra *sh)
{
	char	*expanded;

	expanded = NULL;
	if (*expandable)
	{
		expanded = ft_getenv(&sh->env_list, *expandable);
		if (expanded)
			update_cmd(dol, expanded, sh);
		else
		{
			*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, "");
			sh->i -= sh->len + 1;
		}
		free(*expandable);
		return (1);
	}
	return (0);
}

void	get_hundred_cent(char **fifty_cent, t_infra *sh)
{
	char	*expandable;

	sh->len = 0;
	sh->i = 0;
	char *dol = *fifty_cent;
	while (sh->i < ft_strlen(dol))
	{

		seperate_quote(dol[sh->i], sh);
		if (!(*fifty_cent)[sh->i])
			return ;
		if ((*fifty_cent)[sh->i] == '$' && !sh->single)
		{
			if (!ft_isalpha(dol[++sh->i]))
				continue;
			sh->len = 0;
			while (ft_isalnum(dol[sh->i]))
			{
				sh->len++;
				sh->i++;
			}
			expandable = ft_substr(dol, sh->i - sh->len, sh->len);
			if (expande_it(fifty_cent, &expandable, sh))
				continue ;
		}
		sh->i++;
	}
}