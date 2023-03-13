/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 14:09:18 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	process(t_cmd *cmd, int i, t_exec *exec) //pfd in exec
{
	int		pid;
	char	**env_array;
	char	*c_path;

//what if I initialize env_array and c_path inside child....
//so no need to free in the parent
	env_array = list_to_array(exec->env_list);
	if (ft_strrchr(cmd->main_cmd, '/'))
		cmd->c_path = cmd->main_cmd;
	else
		c_path = check_path(exec->path_array, ft_strjoin("/", cmd->main_cmd));
	pid = fork();
	if (pid_error(pid) == 0)
	{
		ft_dup2(cmd->in_rds, 0);
		//if output redirection exist the below else dup2 to pipe??
		ft_dup2(cmd->out_rds, 1);
		//close fds - for pipes because file fds will be closed in ft_dup2
		mt_arg_error(cmd, env_array, exec);
		if (cmd_is_built_in(cmd->main_cmd))
			ft_built_in(cmd->main_cmd, cmd->cmd_and_args, exec->env_list);
		else if (c_path == NULL || execve(c_path, cmd, env_array) == -1)
			execve_error(exec, cmd);
	}
	//free stuff
	//close the file descriptor (pipes...no need for the file if opening in child)
}

void	ft_dup2(t_rdrct **redirect, int flag)
{
	int	i;
	int	fd;

	while (redirect[i])
	{
		fd = open_file(redirect[i]->file, redirect[i]->sign);
		if (ft_strcmp(redirect[i]->sign, "<<"))
			fd_error(fd, redirect[i]->file);
		if (flag == 0)
			dup2(fd, STDIN_FILENO);
		else if (flag == 1)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
}

int	ft_heredoc(char *delimeter)
{
	int		fd;
	char	*line;

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(delimeter, line) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (fd);
	//unlink temp in the end main
}

int	open_file(char *file, char *redirection)
{
	int	fd;

	if (ft_strcmp(redirection, "<") == 0)
		fd = open(file, O_RDONLY, 0777);
	else if (ft_strcmp(redirection, ">") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (ft_strcmp(redirection, ">>") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (ft_strcmp(redirection, "<<") == 0)
		fd = ft_herdoc(file);
	return (fd);
}

char	**list_to_array(t_env **envlist)
{
	int		list_len;
	char	**array;
	int		i;
	t_env	*t;

	list_len = envlst_len(envlist);
	array = malloc(sizeof(char *) * (list_len + 1));
	i = 0;
	t = *envlist;
	while (t)
	{
		array[i] = malloc(sizeof(char) * (ft_strlen(t->whole)));
		ft_strcpy(array[i], t->whole);
		i++;
		t = t->next;
	}
	return (array);
}
