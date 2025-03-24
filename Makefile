# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 19:42:34 by shattori          #+#    #+#              #
#    Updated: 2025/03/22 18:32:32 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS := -O2
NAME = pipex
SRC_DIR := ./srcs
LIBFT_DIR := ./srcs/libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/error_handling.c $(SRC_DIR)/make_process.c \
       $(LIBFT_AR)

IFLAGS := ./ 
OBJS = $(SRCS:.c=.o)

# デフォルトターゲット
all: $(NAME)

# 実行可能ファイルを作成
$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# libft.a をビルドするターゲット
$(LIBFT_AR):
	make -C $(LIBFT_DIR)

# .c ファイルを .o にコンパイル
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(IFLAGS) -c $< -o $@

# クリーンターゲット（オブジェクトファイルと実行ファイルを削除）
clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_AR)

re: fclean all
