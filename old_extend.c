

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
	char	*quoted;

	// if (!sh->paired)
	// {
	// 	quoted = add_quotes(expanded);
	// 	*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, quoted);
	// 	sh->i += ft_strlen(expanded) - sh->len - 1;
	// 	free(quoted);
	// }
	// else
	// {
		// printf("exp %s\n", expanded);
		// quoted = add_quotes(expanded);
		// printf("quot %s\n", expanded);
		*dol = modify_cmd(*dol, sh->i - sh->len - 1, sh->len + 1, expanded);
		sh->i += ft_strlen(expanded) - sh->len - 1;
	// }
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

void	get_hundred_cent(char **fifty_cent, t_infra *sh)
{
	char	*expandable;
	char	*dol;

	sh->len = 0;
	sh->i = 0;
	dol = *fifty_cent;
	sh->paired = 0;
	sh->single = 0;
	// printf("fresh {%s}\n", (*fifty_cent));
	while (sh->i < ft_strlen((*fifty_cent)))
	{
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
	// printf("%s\n",*fifty_cent );
}