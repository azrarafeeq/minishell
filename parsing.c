/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:21:37 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/20 18:01:34 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	get_line(t_infra *shell, char **envp)
{
	int		len;
	//int		pid;
	t_cmd	*cmds;

	len = 0;
	while (1)
	{
		shell->rd = readline("\e[1;32mchill{😎}>\e[0m ");
		if (!shell->rd || !ft_strcmp(shell->rd, "exit"))
			return (printf("exit\n"), 0);
		if (ft_strcmp(shell->rd, ""))
			add_history(shell->rd);
		shell->trim_rd = ft_strtrim(shell->rd, "\t \n\v\r");
		if (!*shell->trim_rd || !syntax_err(shell))
			continue ;
		shell->cmds = ft_split_with_quotes(shell->trim_rd, '|', &len);
		//free(shell->trim_rd);
		infra_shell(shell, &cmds, len, envp);
		// free_cmds(shell->scmds);
		// free_structs(shell);
		// if(excecute(cmds->cmd))
		// 	continue;
	}
	// how to return pid // if called in a while loop?
}

int	main(int ac, char **av, char **envp)
{
	t_infra	shell;
	int		i;

	(void)av;
	if (ac != 1)
		return (0);
	i = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	get_line(&shell, envp);
	// free(shell.rd);
	// free(shell.trim_rd);
	while (++i < shell.pipe_len)
		waitpid(-1, 0, 0);
	//waitpid with the pid got from pipex and something with the second argument
}
