/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:17:58 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/29 12:22:48 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_init(t_in *in, char *str)
{
	in->i = 0;
	in->j = 0;
	in->k = 0;
	in->quote = 0;
	in->len = ft_strlen(str);
	in->out = (char *) malloc((in->len + 1) * 3 * sizeof(char));
}

char	*epur_str(char *av, t_in *in)
{
	in_init(in, av);
	while (av[in->i])
	{
		is_quote(av[in->i], &in->quote);
		if (!in->quote)
		{
			while (av[in->i] && av[in->i] != ' ')
				in->out[in->k++] = av[in->i++];
			while (av[in->i] && (av[in->i] == ' ' || av[in->i] == '\t'))
			{
				in->j++;
				in->i++;
			}
			if (in->j >= 1)
			{
				in->out[in->k++] = ' ';
				in->j = 0;
			}
		}
		else
			in->out[in->k++] = av[in->i++];
	}
	in->out[in->k] = '\0';
	return (free(av), in->out);
}

char	*replace_with_space(char *input)
{
	t_in	in;

	in_init(&in, input);
	while (in.i < ft_strlen(input))
	{
		is_quote(input[in.i], &in.quote);
		if ((input[in.i] == '>' || input[in.i] == '<') && !in.quote)
		{
			if (input[in.i + 1] == '>' || input[in.i + 1] == '<')
				fill_spaces(&in, input, 0);
			else
				fill_spaces(&in, input, 1);
		}
		else if (input[in.i] == '\t')
			in.out[in.j++] = ' ';
		else
			in.out[in.j++] = input[in.i];
		in.i++;
	}
	in.out[in.j] = '\0';
	return (in.out);
}

void	clean_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	j = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

void	check_quotes(char c, char *single, char *paired)
{
	if (c == '\'')
	{
		if (*single)
			*single = 0;
		else if (!*paired)
			*single = c;
	}
	else if (c == '\"')
	{
		if (*paired)
			*paired = 0;
		else if (!*single)
			*paired = c;
	}
}

int	right_quotes(char *str)
{
	int		i;
	char	single;
	char	paired;

	single = 0;
	paired = 0;
	i = 0;
	while (str[i])
	{
		check_quotes(str[i], &single, &paired);
		i++;
	}
	if (single || paired)
		return (0);
	return (1);
}
