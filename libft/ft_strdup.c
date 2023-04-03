/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:01:42 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/04 01:41:47 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		j;

	j = 0;
	while (s1[j] != '\0')
		j++;
	str = ft_calloc(sizeof(char), (j + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
