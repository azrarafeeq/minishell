/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:26:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/11 22:16:31 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	char	*path;
	t_exec	*exec; //will later be inside a struct

	exec = malloc(sizeof(t_exec));
	exec->pfd = alloc_pipe_fds(exec->cmd_amt - 1);
	exec->env_list = NULL;
	ft_envp(envp, &(exec->env_list));
	path = get_path(&(exec->env_list));
	exec->path_array = path_array(path);
	//ft_pwd();
	//ft_env(&exec->env_list);
	//ft_export(&exec->env_list, NULL);
	//waitpid()
}

void	pipex(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmd_amt)
	{
		if (exec->cmd_amt > 1 && i < (exec->cmd_amt - 1))
			pipe(exec->pfd[i]);
		process(exec->cmds[i], exec, i);
		i++;
	} 
}
