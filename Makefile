NAME		=	cub3D
RM			=	rm -rf
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g #-Wunused -Wuninitialized -Wunreachable-code -g3 # -MMD -fsanitize=address # -Ofast

SRCDIR		=	src
SRC			=	$(shell find $(SRCDIR) -iname "*.c")

OBJDIR		=	.build
OBJ			=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# MLXDIR		:=	lib/MLX42
# MLXBUILD	:=	$(MLXDIR)/build
# MLXA		:=	$(MLXBUILD)/libmlx42.a

LIBXDIR	:=	lib/minilibx_linux
LIBX	:=	$(LIBXDIR)/libmlx_Linux.a

LIBFTDIR	:=	lib/libft
LIBFT		:=	$(LIBFTDIR)/libft.a

SUBMOD		:=	$(LIBFTDIR)/Makefile	#	$(MLXDIR)/CMakeLists.txt

# MLXFLAGS	:=	-ldl -lglfw -pthread -lm
# // The flag (-O3 -ffast-math) is used for optimization.
# // The flag (-framework) is used to specify the required frameworks.
# // the flag (-lglfw) is for linking the glfw library
# // the flag (-L) is for the path to the glfw library
# // the flag (-o) is for the name of the executable file-lmlx_Linux

LIBXFLAGS	:=	-Lmlx_linux  -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
LIBXFLAGS_O	:=	-Imlx

LIB			:=	$(LIBFT)

all:		$(SUBMOD)	$(LIBFT)	$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(OBJ) $(LIBX) $(LIBFT) $(LIBXFLAGS) -o $(NAME)
			@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(LIBXFLAGS_O) -c $< -o $@
			@printf "$(UPDATED)" $@ $(CUR_DIR)

$(SUBMOD):
			git	submodule	init
			git	submodule	update

# $(MLXA):
# 			@cd $(MLXDIR)
# 			@cmake -S $(MLXDIR) -B $(MLXBUILD)
# 			@make -sC $(MLXBUILD) -j4
# 			@cd ..

$(LIBFT):
			@$(MAKE) --no-print-directory -C $(@D) all
			@printf "$(MADE)" $@ $(dir $(abspath $(LIBFT)))

clean:
			$(RM) $(OBJDIR)
			@printf "$(REMOVED)" $(OBJDIR) $(CUR_DIR)

fclean: clean
			$(RM) $(NAME) $(NAME_DEBUG)
			@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:			fclean all

info-%:
	$(info $($*))

.PHONY: all clean fclean re
.SILENT:

# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= \t$(RED)$(BOLD)REMOVED %s (%s) $(RESET)\n
MADE	:= \t$(GREEN)$(BOLD)MAKE -C %s (%s) $(RESET)\n
CREATED	:= \t$(GREEN)$(BOLD)CREATED %s (%s) $(RESET)\n
UPDATED	:= \t$(BLUE)$(BOLD)CREATED OR UPDATED %s (%s) $(RESET)\n
