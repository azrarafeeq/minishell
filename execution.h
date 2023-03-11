/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:21:46 by arafeeq           #+#    #+#             */
/*   Updated: 2023/03/11 21:58:13 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
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

typedef struct s_env{
	char			*var;
	char			*value;
	char			*whole;
	int				pos;
	struct s_env	*next;
}				t_env;

typedef struct s_rdrct{
	char	*sign;
	char	*file;
}				t_rdrct;

typedef struct s_cmd{
	int		cmd_num;
	char	*main_cmd;
	char	**cmd_and_args;
	char	*c_path;
	t_rdrct	**in_rds; //array of struct
	t_rdrct	**out_rds; //array of struct
}				t_cmd;

typedef struct s_exec{
	t_cmd	**cmds;
	int		cmd_amt;
	t_env	*env_list;
	char	**path_array;
	int		**pfd;
}				t_exec;

void	ft_envp(char **envp, t_env **env_list);
t_env	*init_env_node(char *str);
void	ft_env_pos(t_env **env_list);
void	envlst_addback(t_env **lst, t_env *new);
int		envlst_len(t_env **env_list);

void	ft_env(t_env **env_list);
void	ft_export(t_env **env_list, char *str);
void	ft_pwd(void);

void	free_char_array(char **array);

#endif