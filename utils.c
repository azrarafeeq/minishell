/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:17:58 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/22 15:41:51 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *epur_str(char *av)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char quote = 0;
	int len = ft_strlen(av);
    char *out = (char*) malloc((len + 1) * sizeof(char));
	len--;
	while (av[i])
	{
		is_quote(av[i], &quote);
		if(!quote)
		{
			while(av[i] && av[i] != ' ')
			{
				if(av[i] == '\t')
					i++;
				else
			    	out[k++] = av[i++];
			}
			while(av[i]  && av[i] == ' '){
				j++;
				i++;
			}
			if(j >= 1 && i <= len)
			{
			    out[k++] = ' ';
				j = 0;
			}
		}
		else
			out[k++] = av[i++];
	}
	out[k] = '\0';
	return free(av), out;
	// // while(av[i] == ' ' ||  av[i] == '\t'){
	// // 	if(av[i] == '\"' || av[i] == '\'')
	// // 		break;
	// // 	i++;	
	// // }
	// sub = ft_substr(av, i, len+2);	
	// output = ft_strjoin(out, sub);
	// return free(av),free(sub),output;
}

char	*replace_with_space(char *input)
{
	int		i;
	int		j;
	char	*output;
	char	quote;

	output = (char *) malloc((4 * ft_strlen(input) + 1) * sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while (i < ft_strlen(input))
	{
		is_quote(input[i], &quote);
		if ((input[i] == '>' || input[i] == '<') && !quote)
		{
			if (input[i + 1] == '>' || input[i + 1] == '<')
			{
				output[j++] = ' ';
				output[j++] = ' ';
				output[j++] = ' ';
				output[j++] = input[i++];
				output[j++] = input[i];
				output[j++] = ' ';
				output[j++] = ' ';
			}
			else
			{
				output[j++] = ' ';
				output[j++] = ' ';
				output[j++] = ' ';
				output[j++] = input[i];
				output[j++] = ' ';
				output[j++] = ' ';
			}
		}
		else
			output[j++] = input[i];
		i++;
	}
	output[j] = '\0';
	return (output);
}

char	*replace(char *str, char *old, char *newstr)
{
	int		len;
	int		oldlen;
	int		newlen;
	int		count;
	int		j;
	char	*result;

	len = strlen(str);
	oldlen = strlen(old);
	count = 0;
	for (int i = 0; i < len; i++) // can't use for
	{
		if (strchr(old, str[i]) != NULL)
		{
			count++;
		}
	}
	newlen = len + count * (strlen(newstr) - oldlen);
	result = (char *) malloc((newlen + 1) * sizeof(char));
	j = 0;
	for (int i = 0; i < len; i++) // can't use for
	{
		if (strchr(old, str[i]) != NULL)
		{
			ft_strcpy(result + j, newstr);
			j += ft_strlen(newstr);
		}
		else
		{
			result[j] = str[i];
			j++;
		}
	}
	result[j] = '\0';
	return (result);
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

int	right_quotes(char *str)
{
	int	i;
	int	single;
	int	paired;

	single = 0;
	paired = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (single)
				single = 0;
			else if (!paired)
				single = 1;
		}
		else if (str[i] == '\"')
		{
			if (paired)
				paired = 0;
			else if (!single)
				paired = 1;
		}
		i++;
	}
	if (single || paired)
		return (0);
	return (1);
}

// void	free_structs(t_infra *sh)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < sh->pipe_len)
// 	{
// 		if(sh[i].rlen)
// 		{
// 			j = -1;
// 			while (++j < sh[i].rlen)
// 				free(sh[i].red[j].file);
// 			free(sh[i].red);
// 		}
// 		i++;
// 	}
// 	free(sh);
// }