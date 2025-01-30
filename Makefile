#Color Codes

DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
ORANGE  = \033[38;5;208m

FILES				= 

NAME				= philo

CC					= gcc
CCFLAGS				= -Wall -Wextra -Werror #-fsanitize=thread 
MAKEFLAGS			= --no-print-directory
RM					= rm -rf

FILES_PATH			= ./
OBJ_DIR				= .obj/

SRCS				= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
OBJS				= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

vpath %.c $(FILES_PATH)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(CCFLAGS) -o $(NAME)
	@echo "$(GREEN)-== $(NAME) has created! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== all object files have deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)-== all files have deleted! ==-$(DEFAULT)"

push:
	@git add . && \
	@git commit -m "update: $(shell date)" && \
	@git push

re: fclean all

.PHONY: all clean fclean re push