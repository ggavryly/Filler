.PHONY: all, clean, fclean, re.
NAME = ggavryly.filler

LIBFT_PATH = libft/

INC = -I ./include/ -I ./$(LIBFT_PATH)include/

SRCS_NAME =	src/main.c \
			src/parse.c \
			src/start.c \
			src/read.c \
			src/solve.c

SRCO_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(SRCS_NAME) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "\033[32m\033[1m[√] - Binary \033[1;33m\033[4m\033[1m$(NAME)\033[0m\033[1;0m\033[32m\033[1m created.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@rm -rf $(SRCO_NAME)
	@echo "\033[31m\033[1m[X] - \033[4m$(NAME)\033[0m\033[31m\033[1m Objects files removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@rm -rf $(NAME)
	@echo "\033[31m\033[1m[X] - Bin \033[4m$(NAME)\033[0m \033[31m\033[1mremoved.\033[0m"

re: fclean all