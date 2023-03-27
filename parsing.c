/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:21:37 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/27 19:21:15 by arafeeq          ###   ########.fr       */
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
	int		i;
	int		j;
	int		pid;
	t_cmd	*cmds;
	t_env	*env_list;

	env_list = NULL;
	ft_envp(envp, &env_list);
	shell->env_list = env_list;
	while (1)
	{
		i = -1;
		shell->rd = readline("\e[1;32mchill{😎}>\e[0m ");
		if (!shell->rd)
		{
			if (shell)
				free_env_list(&shell->env_list);
			return (printf("exit\n"), 0);
		}
		if (ft_strcmp(shell->rd, ""))
			add_history(shell->rd);
		shell->trim_rd = ft_strtrim(shell->rd, "\t \n\v\r");
		if (!*shell->trim_rd || !syntax_err(shell))
			continue ;
		shell->cmds = ft_split_with_quotes(shell, '|');
		infra_shell(shell, &cmds);
		shell->pipe_len -= 1;
		shell->pfd = alloc_pipe_fds(shell->pipe_len);
		pid = pipex(shell, cmds);
		free_int_array(shell->pfd, shell->pipe_len);
		while (++i < shell->pipe_len)
			waitpid(-1, 0, 0);
		waitpid(pid, &j, 0);
		waitpid_signal(j);
		//if (heredoc_exist(shell, cmds))
			unlink("a!");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_infra	shell;

	(void)av;
	if (ac != 1)
		return (0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	get_line(&shell, envp);
	// free(shell.rd);
	// free(shell.trim_rd);
}
