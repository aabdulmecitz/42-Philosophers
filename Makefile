# Color Codes
DEFAULT  = \033[0m
RED      = \033[1;31m
YELLOW   = \033[1;33m
GREEN    = \033[1;32m
BLUE     = \033[1;36m
ORANGE   = \033[38;5;208m

SRC_DIR   = src/
BONUS_DIR = bonus/

NAME      		= philo
BONUS_NAME      = philo_bonus

FILES     = main philosophers init libft utils
BONUS_FILES = main philo_bonus utils_bonus libft init

CC        = gcc
CFLAGS    = -Wall -Wextra -Werror #-fsanitize=address
RM        = rm -rf
MAKEFLAGS += --no-print-directory

SRCS      = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      = $(addprefix $(SRC_DIR), $(addsuffix .o, $(FILES)))

BONUS_SRCS      = $(addprefix $(BONUS_DIR), $(addsuffix .c, $(BONUS_FILES)))
BONUS_OBJS      = $(addprefix $(BONUS_DIR), $(addsuffix .o, $(BONUS_FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g
	@echo "$(GREEN)-== $(NAME) compiled successfully! ==-$(DEFAULT)"
	@$(RM) $(OBJS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $< $(DEFAULT)"

$(BONUS_DIR)%.o: $(BONUS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $< $(DEFAULT)"

bonus: $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME) -g
	@echo "$(GREEN)-== $(BONUS_NAME) compiled successfully! ==-$(DEFAULT)"
	@$(RM) $(BONUS_OBJS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "$(YELLOW)-== All object files removed! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)-== $(NAME) and $(BONUS_NAME) removed! ==-$(DEFAULT)"

push:
	@git add . && \
	git commit -m "Update: `date '+%Y-%m-%d %H:%M:%S'`" && \
	git push
	@echo "$(GREEN)-== Code pushed to GitHub! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re push
