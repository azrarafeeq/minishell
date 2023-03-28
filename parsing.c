/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:21:37 by ahassan           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/28 16:55:38 by arafeeq          ###   ########.fr       */
=======
/*   Updated: 2023/03/28 17:39:41 by ahassan          ###   ########.fr       */
>>>>>>> 67f64a37912ab9736f4371a6ac7d74eb52d2bfeb
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
	//int		j;
	//int		pid;
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
			if (shell->env_list)
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
		printf("cmd_len = %d\n", cmds[0].cmd_len);
		/* shell->pfd = alloc_pipe_fds(shell->pipe_len);
		pid = pipex(shell, cmds);
		free_int_array(shell->pfd, shell->pipe_len);
		while (++i < shell->pipe_len)
			waitpid(-1, 0, 0);
		waitpid(pid, &j, 0);
		waitpid_signal(j);
		unlink("a!"); */
		free_structs(cmds);
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
}
