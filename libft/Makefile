## Name of Project

NAME = libft.a

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = includes
OBJ_DIR = objs
SRC_DIR = srcs

## Compilating Utilities

FLAGS = -Wall -Wextra -Werror -Ofast
INC = $(INC_DIR:%=-I ./%)
LIB = -L $(LIB_DIR) -lft
MLX = -lmlx -framework OpenGL -framework AppKit
CC = clang $(FLAGS) $(INC)

## List of Functions

SRC_FT =	ft_memset					\
					ft_bzero					\
					ft_memcpy					\
					ft_memccpy				\
					ft_memmove				\
					ft_memchr					\
					ft_memcmp					\
					ft_strlen					\
					ft_strdup					\
					ft_strcpy					\
					ft_strncpy				\
					ft_strcat					\
					ft_strncat				\
					ft_strlcat				\
					ft_strchr					\
					ft_strrchr				\
					ft_strstr					\
					ft_strnstr				\
					ft_strcmp					\
					ft_strncmp				\
					ft_atoi						\
					ft_isalpha				\
					ft_isdigit				\
					ft_isalnum				\
					ft_isascii				\
					ft_isprint				\
					ft_toupper				\
					ft_tolower				\
					ft_memalloc				\
					ft_memdel					\
					ft_strnew					\
					ft_strdel					\
					ft_strclr					\
					ft_striter				\
					ft_striteri				\
					ft_strmap					\
					ft_strmapi				\
					ft_strequ					\
					ft_strnequ				\
					ft_strsub					\
					ft_strjoin				\
					ft_strtrim				\
					ft_strsplit				\
					ft_itoa						\
					ft_putchar				\
					ft_putstr					\
					ft_putendl				\
					ft_putnbr					\
					ft_putchar_fd			\
					ft_putstr_fd			\
					ft_putendl_fd			\
					ft_putnbr_fd			\
					ft_lstnew					\
					ft_lstdelone			\
					ft_lstdel					\
					ft_lstadd					\
					ft_lstiter				\
					ft_lstmap					\
					ft_lst_size				\
					ft_lst_clear			\
					ft_realloc				\
					ft_swap						\
					ft_lst_push_back	\
					ft_lst_push_front	\
					ft_strndup				\
					get_next_line			\
					ft_strjoin_free		\


## List of Utilities

OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[0;37m"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : \0033[0;32m$@\0033[0;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@$(CC) -c $< -o $@
	@echo "$(COLOR)Compilating : \0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[0;37m"

$(NAME): $(OBJ_DIR) $(SRC) $(INC_DIR)/libft.h
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[0;37m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[0;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[0;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/

.PHONY: all clean fclean re norme
