# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 00:24:15 by viclucas          #+#    #+#              #
#    Updated: 2020/02/04 17:29:55 by vimarkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM		:= ft_nm
OTOOL	:= ft_otool
# ============================== #

# ========== Standard ========== #
CC		:= gcc
FLAGS	:= -g  -Wall -Wextra -Werror -fsanitize=address
# ============================== #

# =========== Files ============ #
NM_SRCS_FILES		:=	ft_nm.c		\
						dump_fat_32.c \
						dump_fat_64.c \
						dump_macho_32.c \
						dump_macho_64.c \
						handle_archive.c \
						main.c \
						sup.c \
						swap_uint.c \
						get_ac.c \

OTOOL_SRCS_FILES	:=	main.c \
						ft_otool.c \
						dump_macho_64.c \
						dump_macho_32.c \
						sup.c \
						swap_uint.c \
						handle_archive.c \
						dump_fat_32.c \
						dump_fat_64.c \
						ac_args.c \

NM_HEADERS_FILES	:=	ft_nm.h
OTOOL_HEADERS_FILES	:=	ft_otool.h
# ============================== #

# ========== Sources =========== #
NM_PATH		:= src/nm/
OTOOL_PATH	:= src/otool/
NM_SRCS		:= $(addprefix $(NM_PATH), $(NM_SRCS_FILES))
OTOOL_SRCS	:= $(addprefix $(OTOOL_PATH), $(OTOOL_SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH		:= obj/
NM_OBJS_PATH	:= obj/nm/
OTOOL_OBJS_PATH	:= obj/otool/
NM_OBJS			:= $(addprefix $(NM_OBJS_PATH), $(NM_SRCS_FILES:.c=.o))
OTOOL_OBJS 		:= $(addprefix $(OTOOL_OBJS_PATH), $(OTOOL_SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
NM_HEADERS		:= $(addprefix $(INCLUDES_PATH), $(NM_HEADERS_FILES))
OTOOL_HEADERS	:= $(addprefix $(INCLUDES_PATH), $(OTOOL_HEADERS_FILES))
# ============================== #

.PHONY: all clean fclean re

all: $(NM) $(OTOOL)

$(NM_OBJS_PATH)%.o: $(NM_PATH)%.c $(NM_HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(NM_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OTOOL_OBJS_PATH)%.o: $(OTOOL_PATH)%.c $(OTOOL_HEADERS)
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OTOOL_OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(NM): $(NM_OBJS)
	make -C libft/
	$(CC) $(FLAGS) $(NM_OBJS) -o $@ -L libft/ -lft

$(OTOOL): $(OTOOL_OBJS)
	make -C libft/
	$(CC) $(FLAGS) $(OTOOL_OBJS) -o $@ -L libft/ -lft

clean:
	@rm -fv $(NM_OBJS) $(OTOOL_OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@rm -fv $(NM) $(OTOOL)

re: fclean all
