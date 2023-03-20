/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:06:15 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/20 19:32:53 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void is_quote(char c, char *quote)
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
	char	*str;

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
	if (!ft_strlen(str))
		return (NULL);
	str = ft_strtrim(tmp, " \t");
	return (free(tmp), str);
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
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
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

char	**ft_split_with_quotes(char const *s, char c, int *cnt)
{
	int		i;
	int		h;
	char	*tmp = (char *)s; //why use temp;
	char	**split;
	char	**spaces;

	i = 0;
	h = 0;
	split = ft_split_quote(s, c);
	free(tmp);
	while(split[i])
			printf("%s\n", split[i++]);
	// printf("i == %d\n", i);	
	*cnt = i;
	spaces = malloc(sizeof(*split) * (*cnt + 1));
	h = 0;
	h = -1;
	//bool error = false;
	while(split[++h])
	{
		// if (ft_strchr(split[h], '$'))
			// expansion(&split[h]);
		spaces[h] = epur_str(replace_with_space(split[h]));
	}
	spaces[h] = NULL;
	h = 0;
	free_cmds(split);
	// h = 0;
	// while(spaces[h])
	// 	printf("sp %s\n", spaces[h++]);
	return (spaces);
}