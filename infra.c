/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:21:21 by ahassan           #+#    #+#             */
/*   Updated: 2023/03/29 15:44:19 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_init(t_in *in, char *str)
{
	in->i = 0;
	in->j = 0;
	in->k = 0;
	in->quote = 0;
	in->len = ft_strlen(str);
	in->out = (char *) malloc((in->len + 1) * 3 * sizeof(char));
}

int	get_file(char *str, char **file_name, int i)
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
	(*file_name) = ft_substr(str, start, i - start);
	return (i);
}

void	init_infra(t_infra *shell, t_cmd *cmds, int j)
{
	int		y;
	int		x;
	int		len;
	char	quote;

	y = 0;
	x = -1;
	quote = 0;
	while (shell->cmds[j][++x])
	{
		is_quote(shell->cmds[j][x], &quote);
		if ((shell->cmds[j][x] == '>' || shell->cmds[j][x] == '<') && !quote)
		{
			get_flags(cmds, &j, &x, &y);
			len = get_file(shell->cmds[j], &cmds[j].red[y].file, x + 1);
			clean_quotes(cmds[j].red[y].file);
			get_cmd(shell->cmds[j], cmds->start, len);
			x = -1;
			y++;
		}
	}
}

void	cmds_init(t_cmd **cmds, int h, int j)
{	
	while ((*cmds)[j].cmd[h])
		clean_quotes((*cmds)[j].cmd[h++]);
	(*cmds)[j].main = NULL;
	(*cmds)[j].cmd_id = 0;
	h = 0;
	while ((*cmds)[j].cmd[h])
	{
		if (h == 0)
			(*cmds)[j].main = (*cmds)[j].cmd[h];
		h++;
		(*cmds)[j].cmd_id = j + 1;
	}
	if (!((*cmds)[j].main))
		(*cmds)[j].cmd_len = 0;
	else
		(*cmds)[j].cmd_len = h;
}

void	infra_shell(t_infra *shell, t_cmd **tmp)
{
	t_cmd	*cmds;
	int		h;
	int		j;

	h = 0;
	j = -1;
	*tmp = malloc(sizeof(t_cmd) * (shell->pipe_len));
	cmds = *tmp;
	cmds->start = 0;
	cmds->tmp_cmd = shell->cmds;
	while (++j < shell->pipe_len)
	{		
		cmds[j].red_len = red_count(shell->cmds[j]);
		if (cmds[j].red_len)
			cmds[j].red = malloc(sizeof(t_red) * cmds[j].red_len);
		init_infra(shell, cmds, j);
		cmds[j].cmd = ft_split_quote(shell->cmds[j], ' ');
		h = 0;
		cmds_init(&cmds, h, j);
	}
	cmds->cmd_cnt = j;
	free_char_array(shell->cmds);
}
