/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:59:31 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/03 17:54:40 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expande_it(char **dol, char **expandable, t_infra *sh)
{
	char	*expanded;

	expanded = NULL;
	if (*expandable)
	{
		expanded = ft_getenv(&sh->env_list, *expandable);
		if (expanded)
		{
			*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, expanded);
			sh->i += ft_strlen(expanded) - sh->len - 1;
		}
		else
		{
			*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, "");
			g_exit_stat = 0;
			sh->i -= sh->len + 1;
		}
		free(*expandable);
		return (1);
	}
	return (0);
}

int	get_stat(char **dol, t_infra *sh, char *expandable)
{
	sh->i++;
	if ((*dol)[sh->i] == '?' && (*dol)[sh->i - 1] == '$')
	{
		expandable = ft_itoa(g_exit_stat);
		*dol = modify_cmd(*dol, sh->i - 1, 2, expandable);
		sh->i += ft_strlen(expandable) - 2;
		free(expandable);
		return (1);
	}
	return (0);
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

void	get_expanded(char **dol, t_infra *sh, int flag)
{
	char	*expandable;

	sh->len = 0;
	sh->i = 0;
	while (sh->i < ft_strlen((*dol)))
	{
		if (flag)
			seperate_quote((*dol)[sh->i], sh);
		if (!(*dol)[sh->i])
			return ;
		if ((*dol)[sh->i] == '$' && !sh->single)
		{
			if (get_stat(dol, sh, expandable))
				continue ;
			if (is_alpha_num((*dol), sh))
				continue ;
			expandable = ft_substr((*dol), sh->i - sh->len, sh->len);
			if (expande_it(dol, &expandable, sh))
				continue ;
		}
		sh->i++;
	}
}
