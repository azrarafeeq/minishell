/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:11:23 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 20:02:19 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		ft_dup2(cmd->out_rds, 1);
		if (file_rd_exist(cmd->in_rds) == 0)
			dup2(/* ...[0]*/, STDIN_FILENO);
		if (file_rd_exist(cmd->out_rds) == 0)
			dup2(/* ...[1]*/, STDOUT_FILENO);
		//close fds
		mt_arg_error(cmd, env_array, exec);
		if (cmd_is_built_in(cmd->main_cmd))
			ft_built_in(cmd->main_cmd, cmd->cmd_and_args, exec->env_list);
		else if (c_path == NULL || execve(c_path, cmd, env_array) == -1)
			execve_error(exec, cmd);
	}
	//free stuff
	//close the file descriptor (pipes...no need for the file if opening in child)
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
}
