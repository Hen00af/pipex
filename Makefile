# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shattori <shattori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 19:42:34 by shattori          #+#    #+#              #
#    Updated: 2025/03/21 22:20:55 by shattori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS :=  -O2
NAME = pipex2
SRC_DIR := ./srcs
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/error_handling.c $(SRC_DIR)/make_process.c
IFLAGS := ./ 
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./srcs/libft/
# デフォルトターゲット
all: $(NAME)

# 実行可能ファイルを作成
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	$(MAKE_LIBFT)

$(MAKE_LIBFT): make -C $(LIBFT_DIR)
	

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

