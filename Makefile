# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakobori <hakobori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 20:59:22 by hakobori          #+#    #+#              #
#    Updated: 2024/07/08 22:17:04 by hakobori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		 = minishell
SRCS_DIR	 = ./srcs/
INCLUDE_DIR  = ./includes/
LIBFT_DIR 	 = ./libft/
RL_DIR := $(shell brew --prefix readline)
RL_LIB_DIR 	 = $(addprefix $(RL_DIR)/, lib)
RL_INC_DIR   = $(addprefix $(RL_DIR)/, include)
CFLAGS 		 = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR) -I$(RL_INC_DIR)
LDFLAGS      = -L$(RL_LIB_DIR) -lreadline
SRCS 		 = $(SRCS_DIR)main.c \
			   $(SRCS_DIR)signal.c \
			   $(SRCS_DIR)read.c \
			   $(SRCS_DIR)parser.c \
			   $(SRCS_DIR)lexer.c \
			   $(SRCS_DIR)split_to_token.c \
			   $(SRCS_DIR)quotes.c \
			   $(SRCS_DIR)quotes_2.c \
			   $(SRCS_DIR)set_cmd_info_lst.c \
			   $(SRCS_DIR)info_list_utils.c \
			   $(SRCS_DIR)parse_part1.c \
			   $(SRCS_DIR)doll.c \
			   $(SRCS_DIR)end_status.c \
			   $(SRCS_DIR)get_env.c \
			   $(SRCS_DIR)lst_separate_format.c
OBJS 		 = $(SRCS:.c=.o)
LIBFT 		 = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
