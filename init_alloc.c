/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:05:10 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/12 14:14:02 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	**alloc_pipe_fds(int pipe_amt)
{
	int	i;
	int	**p_fd;

	i = 0;
	//error message when reached the limit....but what is the limit??
	p_fd = malloc(sizeof(int *) * pipe_amt);
	while (i < pipe_amt)
	{
		p_fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (p_fd);
}
