# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 14:17:35 by rgramati          #+#    #+#              #
#    Updated: 2024/08/13 17:57:17 by ycontre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	\033[30;49;3m
RED			=	\033[31;49;3m
GREEN		=	\033[32;49;3m
YELLOW		=	\033[33;49;3m
BLUE		=	\033[34;49;3m
MAGENTA		=	\033[35;49;3m
CYAN		=	\033[36;49;3m
WHITE		=	\033[37;49;3m

BBLACK		=	\033[30;49;3;1m
BRED		=	\033[31;49;3;1m
BGREEN		=	\033[32;49;3;1m
BYELLOW		=	\033[33;49;3;1m
BBLUE		=	\033[34;49;3;1m
BMAGENTA	=	\033[35;49;3;1m
BCYAN		=	\033[36;49;3;1m
BWHITE		=	\033[37;49;3;1m

RESET		=	\033[0m

LINE_CLR	=	\33[2K\r

FILE	=	$(shell ls -lR srcs/ | grep -F .c | wc -l)
CMP		=	1

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME        := libft_malloc_$(HOSTTYPE).so

LFT_DIR 	:=	./libft

LFT			:=	$(LFT_DIR)/libft.a

SRCS_DIR	:=	srcs

OBJS_DIR	:=	.objs

SRC_LST		:=	lst/lst_init.c	\
				lst/lst_utils.c

SRC_MISC	:=	misc/utils.c	\
				misc/search.c	\

ALL_SRCS	:=	malloc.c			\
				realloc.c			\
				calloc.c			\
				free.c				\
				show_alloc_mem.c	\
				$(SRC_LST)			\
				$(SRC_MISC)


SRCS		:=	$(ALL_SRCS:%=$(SRCS_DIR)/%)

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

CC          := cc

CFLAGS      := -g -pthread -Wextra -Werror -Wall -fPIC

IFLAGS		:= -I $(LFT_DIR)/includes -I includes


RM          := rm -rf

MAKEFLAGS   += --no-print-directory

DIR_DUP     = mkdir -p $(@D)

# RULES ********************************************************************** #

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	@cp $(LFT) $@
	@ar rcs $@ $^
	@ln -sf $(NAME) libft_malloc.so
	@printf "$(LINE_CLR)$(BWHITE) $(NAME): PROJECT READY !$(RESET)\n"

$(LFT):
	@make -j -C $(LFT_DIR)

$(OBJS_DIR)/%.o: %.c
	@$(DIR_DUP)
	if [ $(CMP) -eq '1' ]; then \
		printf "\n"; \
	fi;
	@printf "$(LINE_CLR)$(WHITE) $(NAME): $(CMP)/$(FILE) $(BWHITE)$<$(RESET) $(GREEN)compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))
	if [ $(CMP) -eq $(FILE) ]; then \
		printf "$(LINE_CLR)$(WHITE) $(NAME): $(CMP)/$(FILE)\n$(LINE_CLR)$(BGREEN) Compilation done !$(RESET)\n"; \
	fi \

test:
	gcc -g main.c $(IFLAGS) $(LFT) libft_malloc.so -o test

clean:
	@$(RM) $(OBJS)

dclean: clean
	@$(RM) $(OBJS_DIR)

fclean: dclean
	@printf " $(BWHITE)$(NAME):$(BRED) cleaned.$(RESET)\n"
	@$(RM) $(NAME)
	@$(RM) libft_malloc.so
	@$(RM) test
	@$(MAKE) -C $(LFT_DIR) fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

# **************************************************************************** #

.PHONY: all clean fclean dclean re test
.SILENT:
