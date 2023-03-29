/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:55:09 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/29 03:58:34 by ahassan          ###   ########.fr       */
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

void free_trim(char **trim)
{
	if(*trim)
		free(*trim);
	*trim = NULL;	
}

int at_exit(t_infra *shell)
{
	shell->rd = readline("\e[1;32mchill{😎}>\e[0m ");
	if (!shell->rd)
	{
		if (shell->env_list)
			free_env_list(&shell->env_list);
		return (printf("exit\n"), (free_trim(&shell->trim_rd)), 0);
	}
	return 1;
}

int infra(t_infra *shell, t_cmd **cmds)
{
	if (ft_strcmp(shell->rd, ""))
		add_history(shell->rd);
	shell->trim_rd = ft_strtrim(shell->rd, "\t \n\v\r");
	if (!*shell->trim_rd || !syntax_err(shell))
		return 1;
	(*shell).cmds = ft_split_with_quotes(shell, '|');
	free_trim(&shell->trim_rd);
	infra_shell(shell, &*cmds);
	return 42;
}

int	get_line(char **envp)
{
	int		i;
	int		j;
	int		pid;
	t_cmd	*cmds;
	t_infra	shell;
	t_env	*env_list;

	env_list = NULL;
	shell.trim_rd = NULL;
	ft_envp(envp, &env_list);
	shell.env_list = env_list;
	while (1)
	{
		i = -1;
		if(!at_exit(&shell))
			exit(0);
		if(infra(&shell, &cmds) == 1)
			continue;
		shell.pipe_len -= 1;
		shell.pfd = alloc_pipe_fds(shell.pipe_len);
		pid = pipex(&shell, cmds);
		free_int_array(shell.pfd, shell.pipe_len);
		while (++i < shell.pipe_len)
			waitpid(-1, 0, 0);
		waitpid(pid, &j, 0);
		waitpid_signal(j, cmds, &shell);
		unlink("a!");
		free_structs(cmds);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	get_line(envp);
}
