NAME = minishell
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
SRC = functions.c support.c main.c
OBJ = $(SRC:.c=.o)
FT_LNK = -L ./libft -lft
DEP = minishell.h

RED = "\033[1;38;2;225;20;20m"
ORANGE = "\033[1;38;2;255;120;10m"
YELLO = "\033[1;38;2;255;200;0m"
GREEN = "\033[1;38;2;0;170;101m"
LG = "\033[1;38;2;167;244;66m"
BLUE = "\033[1;38;2;50;150;250m"
PURPLE = "\033[1;38;2;150;75;255m"
WHITE = "\033[1;38;2;255;250;232m"

all: $(NAME)

libft/%:
	@echo $(YELLO)
	@make -C libft

$(NAME) : $(OBJ) $(DEP) libft/libft.a
	@echo $(LG)Making $(NAME)
	$(CC) $(CFLAGS) $(FT_LNK) $(SRC) -o $(NAME)

%.o: %.c $(DEP) libft/libft.a
	@echo $(YELLO)Making $@
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make clean -C libft
	@echo $(RED)Cleaning o files
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@echo $(RED)Removing excutables
	@rm -f $(NAME)

re:	fclean all
