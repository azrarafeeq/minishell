# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 19:43:43 by arafeeq           #+#    #+#              #
#    Updated: 2023/03/10 20:13:52 by arafeeq          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = execution env alloc_free built_in #built_in2 

GNLSRCS = ./get_next_line/get_next_line.c\
			./get_next_line/get_next_line_utils.c

OBJDIR = objects

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = -Llibft -lft

$(OBJDIR)/%.o : %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		make all -C libft
		$(CC) $(CFLAGS) $(OBJS) $(GNLSRCS) $(LIBFT) -o $(NAME)

clean :
		make clean -C libft
		rm -rf $(OBJDIR)

fclean : clean
		make fclean -C libft
		rm -f $(NAME)

re : fclean all