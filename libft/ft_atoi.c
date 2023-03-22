/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:59:29 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/22 20:05:10 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ws_and_sign_check(const char *str, int *i, int *ve)
{
	while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v'
		|| str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*ve = -1;
		(*i)++;
	}
	return ;
}

long long	ft_atoi(const char *str)
{
	int					i;
	int					ve;
	unsigned long long	num;

	i = 0;
	ve = 1;
	num = 0;
	ws_and_sign_check(str, &i, &ve);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
		if (num > 9223372036854775807 && ve == 1)
			return (-1);
		if ((num + 1) > 9223372036854775807 && ve == -1)
			return (-1);
	}
	return (num * ve);
}
