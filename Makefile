FILES = check \
		philo \
		utils 

BONUS_FILES = philo_bonus

NAME = philo
BONUS_NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I
MFLAGS = -s -j16 -C
AR = ar rcs
RM = rm -rf

FILES_PATH = src
BONUS_PATH = bonus

SRCS = $(addprefix $(FILES_PATH)/, $(addsuffix .c, $(FILES)))
BONUS = $(addprefix $(BONUS_PATH)/, $(addsuffix .c, $(BONUS_FILES)))
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	$(RM) $(OBJS) $(BONUS_OBJS)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	$(RM) $(OBJS) $(BONUS_OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean libclean
	$(RM) $(NAME)
	$(RM) $(AR_NAME)
	$(RM) $(CHECKER_NAME)

re: fclean all

push:
	git add .
	git commit -m "commit"
	git push

run: re
	./$(NAME) <sth>

.PHONY: all clean fclean re bonus push compile_libs update run