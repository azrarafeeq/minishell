/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:59:54 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/10 22:07:57 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	char	*st1;
	char	*st2;
	int		i;

	st1 = (char *)s1;
	st2 = (char *)s2;
	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	if (s1[0] == '\0' && (s2[0] == '\n' || s2[0] == '\n'))
		return (0);
	while (st1[i] && st2[i] && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}
