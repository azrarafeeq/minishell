/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:04:57 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/02 16:05:10 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_exist(t_infra *shell, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	while (j < cmd[i].red_len)
	{
		if (cmd[i].red[j].flag == HERE_DOC)
			return (1);
		j++;
	}
	return (0);
}
