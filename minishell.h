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
# define DOL '$'
# define SYN_ERR "syntax error near unexpected token\n"

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

int	g_exit_stat;

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
	int		no_expand;
}				t_red;

typedef struct s_cmd{
	int		cmd_id;
	int		start;
	char	*main;
	char	**t_c;
	char	**cmd;
	char	*p;
	int		red_len;
	int		cmd_len;
	int		cmd_cnt;
	t_red	*red;
}				t_cmd;

typedef struct s_infra{
	char	*rd;
	char	*trim_rd;
	char	**cmds;
	t_env	*env_list;
	int		pipe_len;
	char	**env_a;
	int		**pfd;
	int		i;
	int		no_expand;
	int		len;
	char	single;
	char	paired;
}				t_infra;

typedef struct s_in{
	int		i;
	int		j;
	int		k;
	int		len;
	char	quote;
	char	*out;
}t_in;

void	in_init(t_in *in, char *str);
void	is_quote(char c, char *quote);
int		right_quotes(char *str);
void	clean_quotes(char *str);
void	handler(int sig);
char	**ft_split_quote(char const *s, char c);
char	**ft_split_with_quotes(t_infra *shell, char c);
void	seperate_quote(char cur, t_infra *sh);
char	*replace_with_space(char *input);
void	fill_spaces(t_in *in, char *input, int flag);
char	*epur_str(char *av, t_in *in);
char	*modify_cmd(char *dol, int start, int len, char *extended);
void	get_cmd(char *s, unsigned int start, size_t len);
int		red_count(char *str);
int		check_redirect(char *str);
void	get_flags(t_cmd *cmds, int *j, int *x, int *y);
void	infra_shell(t_infra *shell, t_cmd **tmp);
void	get_expanded(char **fifty_cent, t_infra *sh, int flag);
int		check_pipes(char *line);
int		**alloc_pipe_fds(int pipe_amt);

void	ft_envp(char **envp, t_env **env_list);
char	*ft_getenv(t_env **env, char *str);
t_env	*init_env_node(char *str);
void	ft_env_pos(t_env **env_list);
void	ft_env_pos2(t_env *t2, t_env *t, int *i, int *j);
void	envlst_addback(t_env **lst, t_env *new);
int		envlst_len(t_env **env_list);
char	**list_to_array(t_env **envlist);

int		paths_count(char *path);
char	*get_path(t_env **env_list);
char	*append_path_to_array(char *path, int *i);
char	**path_array(char *path);
char	*check_path(char **path_array, char *command);

void	execute(t_infra *shell, t_cmd *cmds);
int		pipex(t_infra *shell, t_cmd *cmds);
int		process(t_cmd *cmd, int i, t_infra *shell, int *fd);
int		parent_process(t_cmd *cmd, int i, t_infra *shell);
int		open_file(t_red red, int in_fd, t_infra *shell);
int		ft_dup2(t_infra *shell, t_cmd *cmds, int i, int flag);
void	ft_pipe_dup2(t_infra *shell, t_cmd *cmds, int i);
void	ft_heredoc(t_red red, int in_fd, t_infra *shell);
int		heredoc_exist(t_cmd *cmd, int i);
int		file_rd_exist(t_cmd cmd, int flag1, int flag2);
int		var_exist(t_env **env_list, char *str);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
void	ft_close_pipes(t_infra *shell, int i, t_cmd cmd);

int		cmd_is_built_in(char *str);
void	ft_built_in(t_cmd cmd, t_infra *shell, t_cmd *cmds);
void	ft_cd(char **str, t_env **env_list);
void	ft_env(t_env **env_list);
void	ft_unset(t_env **env, char **str);
void	delete_node(t_env **env, t_env *temp, t_env *prev);
void	ft_pwd(void);
void	ft_echo(char **str);
void	ft_export(t_env **env_list, char **str);
void	print_export(t_env **env_list);
void	ft_exit(int g_exit_stat);
void	ft_exit_cmd(char **str, t_infra *shell, t_cmd *cmds);

void	hd_handler(int sig);
void	qhandler(int sig);
void	waitpid_signal(int j, t_cmd *cmds, t_infra *shell);
void	handler(int sig);
void	update_pwd(t_env **env_list, char *cur_pwd, char *pwd);
void	update_oldpwd(t_env **env_list, char *cur_pwd);
void	update_var(t_env **env_list, char *str);

int		syntax_err(t_infra *in);
void	mt_arg_error(t_infra *shell, t_cmd *cmds, int j);
void	execve_error(t_infra *shell, t_cmd *cmd, int i);
int		fd_error(t_red red, t_infra *shell, t_cmd *cmds, int i);
int		export_unset_error(char *str, int flag);
void	exit_error(char *str, int flag);

void	free_char_array(char **array);
void	free_int_array(int **int_array, int len);
void	free_env_list(t_env **env_list);
void	free_shell_cmds_in_child(t_infra *shell, t_cmd *cmds);
void	free_structs(t_cmd *cmd);
void	free_trim(char **trim);

#endif