# Color Codes
DEFAULT  = \033[0m
RED      = \033[1;31m
YELLOW   = \033[1;33m
GREEN    = \033[1;32m
BLUE     = \033[1;36m
ORANGE   = \033[38;5;208m

SRC_DIR   = src/
NAME      = philo
FILES     = main philosophers sth utils

CC        = gcc
CFLAGS    = -Wall -Wextra -Werror #-fsanitize=thread
RM        = rm -rf
MAKEFLAGS += --no-print-directory

SRCS      = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      = $(addprefix $(SRC_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)-== $(NAME) compiled successfully! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $< $(DEFAULT)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(ORANGE)Created object directory: $(OBJ_DIR)$(DEFAULT)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)-== All object files removed! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)-== $(NAME) removed! ==-$(DEFAULT)"

push:
	@git add . && \
	git commit -m "Update: `date '+%Y-%m-%d %H:%M:%S'`" && \
	git push
	@echo "$(GREEN)-== Code pushed to GitHub! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re push