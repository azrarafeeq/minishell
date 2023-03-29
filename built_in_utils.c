/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:42:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/29 20:18:54 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_env **env, t_env *temp, t_env *prev)
{
	if (temp == *env)
		(*env) = (*env)->next;
	else if (temp->next == NULL)
		prev->next = NULL;
	else
		prev->next = temp->next;
	free(temp->var);
	free(temp->value);
	free(temp);
}
