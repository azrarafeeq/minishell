/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:21:21 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/20 21:50:28 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i < start || i >= len)
		{
			s[j] = s[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
}

void	get_file(char *str, char **file_name, int i, t_vars *var)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (str[i])
	{
		is_quote(str[i], &quote);
		if ((str[i] == ' ' || str[i] == '\t') && !quote)
			break ;
		i++;
	}
	var->i = i;
	(*file_name) = ft_substr(str, start, i - start);
}

int	red_count(char *str)
{
	int		i;
	int		num;
	char	quote;

	i = 0;
	num = 0;
	quote = 0;
	while (str[i])
	{
		is_quote(str[i], &quote);
		if (!quote && (str[i] == '>' || str[i] == '<'))
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			num++;
		}
		i++;
	}
	return (num);
}

void	get_flags(t_infra *shell, t_cmd *cmds, t_vars *var)
{
	var->start = var->x - 1;
	if (shell->cmds[var->j][var->x + 1] == '>' \
		|| shell->cmds[var->j][var->x + 1] == '<')
	{
		if (shell->cmds[var->j][var->x + 1] == '>')
			cmds[var->j].red[var->y].flag = APPEND;
		else if (shell->cmds[var->j][var->x + 1] == '<')
			cmds[var->j].red[var->y].flag = HERE_DOC;
		var->x = var->x + 2;
	}
	else if (shell->cmds[var->j][var->x] == '>')
	{
		cmds[var->j].red[var->y].flag = TRUNCATE;
		var->x++;
	}
	else if (shell->cmds[var->j][var->x] == '<')
	{
		cmds[var->j].red[var->y].flag = IN_FILE;
		var->x++;
	}
}

void	init_infra(t_infra *shell, t_cmd *cmds, t_vars *v)
{
	v->y = 0;
	v->x = -1;
	while (shell->cmds[v->j][++v->x])
	{
		if (shell->cmds[v->j][v->x] == '"' || shell->cmds[v->j][v->x] == '\'')
		{
			if (v->quote == 0)
				v->quote = shell->cmds[v->j][v->x];
			else if (v->quote == shell->cmds[v->j][v->x])
				v->quote = 0;
		}
		if ((shell->cmds[v->j][v->x] == '>' || \
			shell->cmds[v->j][v->x] == '<') && !v->quote)
		{
			get_flags(shell, cmds, v);
			get_file(shell->cmds[v->j], \
				&cmds[v->j].red[v->y].file, v->x + 1, v);
			clean_quotes(cmds[v->j].red[v->y].file);
			get_cmd(shell->cmds[v->j], v->start, v->i);
			v->x = v->start - 1;
			printf("\e[1;34mfile name : %s\n\e[0m", cmds[v->j].red[v->y].file);
			printf("\e[1;34mflag	  : %d\n\e[0m", cmds[v->j].red[v->y].flag);
			v->y++;
		}
	}
}

void	infra_shell(t_infra *shell, t_cmd **tmp, int len, char **envp)
{
	t_cmd	*cmds;
	t_vars	var;
	int		pid;

	var.start = 0;
	var.quote = 0;
	var.h = 0;
	var.j = -1;
	var.x = 0;
	*tmp = malloc(sizeof(t_cmd) * len);
	cmds = *tmp;
	cmds->cmd_len = len;
	while (++var.j < len)
	{
		cmds[var.j].red_len = red_count(shell->cmds[var.j]);
		if (cmds[var.j].red_len)
			cmds[var.j].red = malloc(sizeof(t_red) * cmds[var.j].red_len);
		init_infra(shell, cmds, &var);
		cmds[var.j].cmd = ft_split_quote(shell->cmds[var.j], ' ');
		var.h = 0;
		while (cmds[var.j].cmd[var.h])
			clean_quotes(cmds[var.j].cmd[var.h++]);
		var.h = 0;
		cmds[var.j].main = NULL;
		while (cmds[var.j].cmd[var.h])
		{
			if (var.h == 0)
			{
				cmds[var.j].main = cmds[var.j].cmd[var.h];
				printf("\e[0;31mmain[%d]-> %s\n\e[0m",var.j, cmds[var.j].main);
			}
			printf("cmd %s\n", cmds[var.j].cmd[var.h++]);
			cmds[var.j].cmd_id = var.j + 1;
		}
		printf("cmd_id = %d\n", cmds->cmd_id);
		printf("num of CMD %d\n", cmds->cmd_id);
		printf("--------------\n");
	}
	shell->pipe_len = len - 1;
	printf("pipe_len = %d\n", shell->pipe_len);
	shell->pfd = alloc_pipe_fds(shell->pipe_len);
	t_env *env_list = NULL;
	ft_envp(envp, &env_list);
	char *path = get_path(&env_list);
	shell->path_array = path_array(path);
	shell->env_list = env_list;
	pid = pipex(shell, cmds, &env_list);
	waitpid(pid, 0, 0);
}
