/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:06:15 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/02 19:19:35 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_quote(char c, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (!*quote)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}

static char	*ft_copy(char const *s, char c, int *i)
{
	char	quote;
	char	*tmp;

	quote = 0;
	*i = 0;
	while (s[*i])
	{
		is_quote(s[*i], &quote);
		if (!quote && s[*i] == c)
			break ;
		(*i)++;
	}
	tmp = ft_substr(s, 0, *i);
	return (tmp);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	cnt;
	size_t	word;
	char	quote;

	i = 0;
	cnt = 0;
	word = 0;
	quote = 0;
	while (s[i])
	{
		is_quote(s[i], &quote);
		if (s[i] == c && !quote)
			cnt = 0;
		if (!quote && s[i] != c && cnt == 0)
		{
			word++;
			cnt = 1;
		}
		i++;
	}
	return (word);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**split;
	size_t	j;
	int		i;
	int		len;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = malloc(sizeof(*split) * (count_word(s, c) + 1));
	if (!split)
		return (NULL);
	while (j < count_word(s, c))
	{
		while ((s[i] == c || s[i] == ' ' || s[i] == '\t') && s[i])
			i++;
		split[j++] = ft_copy(s + i, c, &len);
		i += len;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split_with_quotes(t_infra *shell, char c)
{
	int		h;
	char	**split;
	char	**spaces;
	t_in	in;

	h = 0;
	in.out = NULL;
	shell->paired = 0;
	shell->single = 0;
	shell->len = 0;
	shell->i = 0;
	shell->pipe_len = count_word(shell->trim_rd, c);
	split = ft_split_quote(shell->trim_rd, c);
	spaces = malloc(sizeof(*split) * (shell->pipe_len + 1));
	h = 0;
	h = -1;
	while (split[++h])
	{
		if (ft_strchr(split[h], HUNDRED_CENT) && \
			ft_strncmp((char *)ft_strchr(split[h], '<'), "<<", 2) != 0)
			get_hundred_cent(&split[h], shell, 1);
		spaces[h] = epur_str(replace_with_space(split[h]), &in);
	}
	spaces[h] = NULL;
	free_char_array(split);
	return (spaces);
}
