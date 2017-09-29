## Name of Project

NAME = fdf

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs
LIB_DIR = libs

## Compilating Utilities

FLAGS = -Wall -Wextra -Werror
INC = $(INC_DIR:%=-I ./%)
LIB = -L $(LIB_DIR) -lft -lmlx
MLX = -framework OpenGL -framework AppKit
CC = clang $(FLAGS) $(INC)


# libraries
LIB_FT				:=	./libft
LIB_FT_INC		:=	-I $(LIB_FT)/includes/
LIB_FT_LINK		:=	-L $(LIB_FT) -l ft

LIB_MLX			:=	./minilibx/
LIB_MLX_INC		:=	-I $(LIB_MLX)
LIB_MLX_LINK	:=	-L $(LIB_MLX) -l mlx -framework OpenGL -framework Appkit

# our project
INCLUDES		:=	$(LIB_FT_INC) $(LIB_MLX_INC) -I $(INC_DIR)
LINK			:=	$(LIB_FT_LINK) $(LIB_MLX_LINK)

## List of Functions

SRC_FT =	 	fdf \
		 			fill_memory


## List of Utilities

ALL_OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o) $(LIB_FT	:%=$(OBJ_DIR)/%.o) $(LIB_MLX	:%=%.o)
OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[0;37m"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : \0033[0;32m$@\0033[0;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/fdf.h
	@$(CC) -c $< -o $@
	@echo "$(COLOR)Compilating : \0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[0;37m"

$(NAME): $(OBJ_DIR) $(SRC) $(INC_DIR)/fdf.h
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[0;37m"
	@make -C $(LIB_FT)
	@make -C $(LIB_MLX)
	@$(CC) $(LINK) $(OBJ) $(MLX) -o $@
	@echo "$(COLOR)$(NAME)\t\t\0033[0;32m[Created]\0033[0;37m"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_FT) clean
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[0;37m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_FT) fclean
	@make -C $(LIB_MLX) clean
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[0;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/
	@make norme -C $(LIB_FT)

.PHONY: all clean fclean re norme
