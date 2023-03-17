/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:26:24 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/17 06:45:04 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pid;
	t_exec	*exec;
	(void)argv;
	(void)argc;

	i = -1;
	exec = malloc(sizeof(t_exec));
	pid = pipex(exec);
	while (++i < exec->cmd_amt)
		waitpid(-1, 0, 0);
	//waitpid with th epid got from pipex and something with the second argument
}

int	pipex(t_exec *exec)
{
	int	i;
	int	pid;

	i = 0;
	if (exec->cmd_amt > 1)
		pipe(exec->pfd[0]);
	while (i < exec->cmd_amt)
	{
		if (i < exec->cmd_amt - 1)
			pipe(exec->pfd[i + 1]);
		pid = process(exec->cmds[i], i, exec);
		i++;
	}
	if (heredoc_exist(exec->cmds))
		unlink("temp");
	return (pid);
}
