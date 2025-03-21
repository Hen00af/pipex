# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 19:42:34 by shattori          #+#    #+#              #
#    Updated: 2025/03/14 19:26:36 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS :=  -O2
NAME = pipex
SRC_DIR := srcs
SRCS = ./main.c
IFLAGS := ./ 
OBJS = $(SRCS:.c=.o)

# デフォルトターゲット
all: $(NAME)

# 実行可能ファイルを作成
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# オブジェクトファイルの生成
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS)

# フルクリーンアップ（実行ファイルも削除）
fclean: clean
	rm -f $(NAME)

# 再構築（クリーン→all）
re: fclean all

