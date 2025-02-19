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
BONUS_FILES = main philo_bonus utils_bonus libft int

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

$(BONUS_SRCS)%.o: $(BONUS_OBJS)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Compiling: $< $(DEFAULT)"

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

run:
	@echo "Running tests..."
	@echo "----------------------------------------"
	@echo "Test 1: 1 philosopher"
	./$(NAME) 1 800 200 200
	@echo "----------------------------------------"
	# @echo "Test 2: 5 philosophers, 800ms death time EXPECTION: NO DIE"
	# ./$(NAME) 5 800 200 200
	@echo "----------------------------------------"
	@echo "Test 3: 5 philosophers, 410ms death time EXPECTION: NO DIE"
	./$(NAME) 5 410 200 200
	@echo "----------------------------------------"
	@echo "Test 4: 4 philosophers, 410ms death time, 10 meals"
	./$(NAME) 4 410 200 200 10
	@echo "----------------------------------------"
	@echo "Test 5: 10 philosophers, 800ms death time EXPECTION: NO DIE"
	./$(NAME) 10 800 200 200
	@echo "----------------------------------------"
	@echo "Test 6: 10 philosophers, 800ms death time, 5 meals"
	./$(NAME) 10 800 200 200 5
	@echo "----------------------------------------"
	@echo "Tests completed."

.PHONY: all clean fclean re push run
