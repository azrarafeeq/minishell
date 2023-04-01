/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:48:18 by arafeeq           #+#    #+#             */
/*   Updated: 2023/04/01 03:30:01 by ahassan          ###   ########.fr       */
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

int	at_exit(t_infra *shell)
{
	shell->rd = readline("\e[1;32mchill{😎}>\e[0m ");
	if (!shell->rd)
	{
		if (shell->env_list)
			free_env_list(&shell->env_list);
		return (printf("exit\n"), (free_trim(&shell->trim_rd)), 0);
	}
	return (1);
}

int	infra(t_infra *shell, t_cmd **cmds)
{
	if (ft_strcmp(shell->rd, ""))
		add_history(shell->rd);
	shell->trim_rd = ft_strtrim(shell->rd, "\t \n\v\r");
	if (!shell->trim_rd || !*shell->trim_rd || !syntax_err(shell))
		return (free_trim(&shell->trim_rd), (1));
	(*shell).cmds = ft_split_with_quotes(shell, '|');
	free_trim(&shell->trim_rd);
	infra_shell(shell, &*cmds);
	return (42);
}

int	get_line(char **envp)
{
	t_cmd	*cmds;
	t_infra	shell;
	t_env	*env_list;

	env_list = NULL;
	shell.trim_rd = NULL;
	ft_envp(envp, &env_list);
	shell.env_list = env_list;
	g_exit_stat = 0;
	print_prompt();
	while (1)
	{
		if (!at_exit(&shell))
			exit(0);
		if (infra(&shell, &cmds) == 1)
			continue ;
		execute(&shell, cmds);
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
