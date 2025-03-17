# Color Codes
DEFAULT  = \033[0m
RED      = \033[1;31m
YELLOW   = \033[1;33m
GREEN    = \033[1;32m
BLUE     = \033[1;36m
ORANGE   = \033[38;5;208m

SRC_DIR   = src/
NAME      = philo
FILES     = main philosophers init libft utils

CC        = cc
CFLAGS    = -Wall -Wextra -Werror -fsanitize=thread -o1
RM        = rm -rf
MAKEFLAGS += --no-print-directory

SRCS      = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      = $(addprefix $(SRC_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)-== $(NAME) compiled successfully! ==-$(DEFAULT)"
	@$(RM) $(OBJS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $< $(DEFAULT)"

go: all clean
	@clear

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== All object files removed! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)-== $(NAME) removed! ==-$(DEFAULT)"

push:
	@git add . && \
	git commit -m "Update" && \
	git push
	@echo "$(GREEN)-== Code pushed to GitHub! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re push
