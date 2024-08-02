# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkawahar <rkawahar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 20:59:22 by hakobori          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/08/01 17:38:34 by rkawahar         ###   ########.fr        #
=======
#    Updated: 2024/08/02 13:40:12 by hakobori         ###   ########.fr        #
>>>>>>> refs/remotes/origin/main
#                                                                              #
# **************************************************************************** #

NAME 		 = minishell
SRCS_DIR	 = ./srcs/
BILT_DIR     = ./builtin/
INCLUDE_DIR  = ./includes/
LIBFT_DIR 	 = ./libft/
RL_DIR := $(shell brew --prefix readline)
RL_LIB_DIR 	 = $(addprefix $(RL_DIR)/, lib)
RL_INC_DIR   = $(addprefix $(RL_DIR)/, include)
CFLAGS 		 = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(RL_INC_DIR)
# CFLAGS		+= -g -fsanitize=address
LDFLAGS      = -L$(RL_LIB_DIR) -lreadline
SRCS 		 = $(SRCS_DIR)main.c \
			   $(SRCS_DIR)signal.c \
			   $(SRCS_DIR)signal2.c \
			   $(SRCS_DIR)signal3.c \
			   $(SRCS_DIR)read.c \
			   $(SRCS_DIR)parser.c \
			   $(SRCS_DIR)parser2.c \
			   $(SRCS_DIR)lexer.c \
			   $(SRCS_DIR)split_to_token.c \
			   $(SRCS_DIR)quotes.c \
			   $(SRCS_DIR)quotes_2.c \
			   $(SRCS_DIR)set_cmd_info_lst.c \
			   $(SRCS_DIR)info_list_utils.c \
			   $(SRCS_DIR)doll.c \
			   $(SRCS_DIR)end_status.c \
			   $(SRCS_DIR)get_env.c \
			   $(SRCS_DIR)lst_separate_format.c \
			   $(SRCS_DIR)here_document.c \
			   $(SRCS_DIR)here_document2.c \
			   $(SRCS_DIR)utils3.c \
			   $(SRCS_DIR)pronpts.c \
			   $(SRCS_DIR)here_doc_pipe.c \
			   $(SRCS_DIR)prosses.c \
			   $(SRCS_DIR)list.c \
			   $(SRCS_DIR)path.c \
			   $(SRCS_DIR)path2.c \
			   $(SRCS_DIR)pipe.c \
			   $(SRCS_DIR)family_process.c \
			   $(SRCS_DIR)infile.c \
			   $(SRCS_DIR)outfile.c \
			   $(SRCS_DIR)re_process.c \
			   $(SRCS_DIR)utils1.c \
			   $(SRCS_DIR)utils2.c \
			   $(SRCS_DIR)lexer2.c \
			   $(SRCS_DIR)fce.c \
			   $(SRCS_DIR)path3.c \
			   $(SRCS_DIR)error.c \
			   $(BILT_DIR)builtin.c \
			   $(BILT_DIR)echo.c \
			   $(BILT_DIR)pwd.c \
			   $(BILT_DIR)add_emv.c \
			   $(BILT_DIR)add_env2.c \
			   $(BILT_DIR)create_export.c \
			   $(BILT_DIR)create_export2.c \
			   $(BILT_DIR)export.c \
			   $(BILT_DIR)export2.c \
			   $(BILT_DIR)export3.c \
			   $(BILT_DIR)remove_exp.c \
			   $(BILT_DIR)env.c \
			   $(BILT_DIR)exit.c \
			   $(BILT_DIR)exit2.c \
			   $(BILT_DIR)home_utils.c \
			   $(BILT_DIR)cd.c \
			   $(BILT_DIR)cd2.c \
			   $(BILT_DIR)cd3.c \
			   $(BILT_DIR)unset.c

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
