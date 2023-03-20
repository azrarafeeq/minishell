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

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH 1024

# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

int	exit_stat;

enum e_types
{
	IN_FILE,
	TRUNCATE,
	APPEND,
	HERE_DOC,
};

typedef struct s_env{
	char			*var;
	char			*value;
	int				pos;
	struct s_env	*next;
}				t_env;

typedef struct s_red{
	int		flag;
	char	*file;
}				t_red;

typedef struct s_cmd{
	int		cmd_id;
	char	*main;
	char	**cmd;
	char	*path;
	int		red_len;
	int		cmd_len;
	t_red	*red;
}				t_cmd;

typedef struct s_infra{
	char	*rd;
	char	*trim_rd;
	char	**cmds;
	t_env	*env_list;
	int		pipe_len;
	char	**path_array;
	int		**pfd;
}				t_infra;

typedef struct s_vars
{
	int		i;
	int		j;
	int		h;
	int		len;
	char	quote;
	char	single;
	char	paired;
	int		x;
	int		start;
	int		y;
}	t_vars;

int		get_line(t_infra *shell, char **envp);
char	*replace(char *str, char *old, char *newstr);
int		right_quotes(char *str);
void	clean_quotes(char *str);
int		check_redirect(char *str);
int		check_pipes(char *line);
void	is_quote(char c, char *quote);
int		syntax_err(t_infra *in);
char	**ft_split_with_quotes(char const *s, char c, int *cnt);
char	**ft_split_quote(char const *s, char c);
void	infra_shell(t_infra *pipe, t_cmd **tmp, int len, char **envp);
void	free_cmds(char **cmds);
char	*replace_with_space(char *input);
void	free_structs(t_infra *sh);
char	*epur_str(char *av);
void	expansion(char **str);
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

int		pipex(t_infra *shell, t_cmd *cmds, t_env **env_list);
int		process(t_cmd *cmd, int i, t_infra *shell, t_env **env_list);
void	ft_dup2(t_red *redirect, int red_len, t_infra *shell, t_cmd *cmds);
void	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i);
int		ft_heredoc(char *delimeter);
int		file_rd_exist(t_cmd cmd, int flag1, int flag2);
int		heredoc_exist(t_infra *shell, t_cmd *cmd);
int		var_exists(t_env **env_list, char *str);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	ft_close_pipes(t_infra *shell, int i, t_cmd cmd);
int		cmd_is_built_in(char *str);

void	ft_cd(char **str, t_env **env_list);
void	ft_built_in(char *cmd, char **args, t_env **env);
void	ft_env(t_env **env_list);
void	ft_export(t_env **env_list, char **str);
void	ft_unset(t_env **env, char **str);
void	ft_pwd(void);
void	ft_echo(char **str);
void	ft_echo_expand(char *str, t_env **env);
void	ft_exit(int exit_stat);

void	update_pwd(t_env **env_list);
void	update_oldpwd(t_env **env_list, char *cur_pwd);
void	update_var(t_env **env_list, char *str);

void	mt_arg_error(t_cmd cmd, char **env_arr, t_infra *exec);
void	execve_error(t_infra *shell, t_cmd *cmd, int i);
int		fd_error(int fd, char *file, t_infra *shell, t_cmd *cmds);
void	export_error(char **str);
void	exit_error(char *str, int flag);

void	free_char_array(char **array);
void	free_int_array(int **int_array, int len);
void	free_cmd(t_cmd **cmd);
void	free_shell(t_infra *shell);

#endif