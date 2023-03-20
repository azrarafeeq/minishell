# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 19:43:43 by arafeeq           #+#    #+#              #
#    Updated: 2023/03/20 15:02:39 by arafeeq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = parsing utils redirection pipe_err err_handling pipe_split infra\
		exec prcs prcs_utils utils2 env path built_in built_in2 free\
		error update

GNLSRCS = ./get_next_line/get_next_line.c\
			./get_next_line/get_next_line_utils.c

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/Cellar/readline/8.1/include -I/usr/local/opt/readline/include/

LIBFT = -Llibft -lft

READLINE = -L/usr/local/opt/readline/lib -lreadline

$(OBJDIR)/%.o : %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C libft
		$(CC) $(CFLAGS) $(OBJS) $(GNLSRCS) $(LIBFT) -o $(NAME) $(READLINE)

clean :
		make clean -C libft
		rm -rf $(OBJDIR)

fclean : clean
		make fclean -C libft
		rm -f $(NAME)

re : fclean all