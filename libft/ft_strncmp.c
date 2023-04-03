/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:55:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/03 13:28:04 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;
	unsigned int	i;

	if (!s1)
		return (-5);
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (s1[0] == '\0' && s2[0] == '\n' && n == 0)
		return (0);
	while (i < n - 1 && st1[i] != '\0' && st2[i] != '\0' && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}
