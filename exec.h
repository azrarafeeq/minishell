/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:46 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/13 14:13:25 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# define MAX_PATH 1024

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

int	err_num;

typedef struct s_env{
	char			*var;
	char			*value;
	char			*whole;
	int				pos;
	struct s_env	*next;
}				t_env;

typedef struct s_rdrct{
	int		flag;
	char	*file;
}				t_rdrct;

typedef struct s_cmd{
	int		cmd_num;
	char	*main;
	char	**cmd_args;
	char	*path;
	t_rdrct	**rds;
}				t_cmd;

typedef struct s_exec{
	t_env	*env_list;
	int		cmd_amt;
	t_cmd	**cmds;
	char	**path_array;
	int		**pfd;
}				t_exec;

int		**alloc_pipe_fds(int pipe_amt);

void	ft_envp(char **envp, t_env **env_list);
char	*ft_getenv(t_env **env, char *str);
t_env	*init_env_node(char *str);
void	ft_env_pos(t_env **env_list);
void	envlst_addback(t_env **lst, t_env *new);
int		envlst_len(t_env **env_list);
char	**list_to_array(t_env **envlist);

int		paths_count(char *path);
char	*get_path(t_env **env_list);
char	*append_path_to_array(char *path, int *i);
char	**path_array(char *path);
char	*check_path(char **path_array, char *command);

void	pipex(t_exec *exec);
int		process(t_cmd *cmd, int i, t_exec *exec);
int		ft_heredoc(char *delimeter);
int		open_file(char *file, int flag);
int		file_rd_exist(t_rdrct **rds, int flag1, int flag2);
int		heredoc_exist(t_cmd **cmd);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
int		cmd_is_built_in(char *str);

void	ft_cd(char **str);
void	ft_built_in(char *cmd, char **args, t_env **env);
void	ft_env(t_env **env_list);
void	ft_export(t_env **env_list, char **str);
void	ft_unset(t_env **env, char **str);
void	ft_pwd(void);
void	ft_echo(char **str, t_env **env);
void	ft_echo_expand(char *str, t_env **env);
void	ft_exit(int err_num);

void	mt_arg_error(t_cmd *cmd, char **env_arr, t_exec *exec);
void	execve_error(t_exec *exec, t_cmd *cmd);
int		fd_error(int fd, char *file);
int		pid_error(int pid);

void	free_char_array(char **array);
void	free_int_array(int **int_array, int len);
void	free_cmd(t_cmd **cmd);
void	free_exec(t_exec *exec);

#endif