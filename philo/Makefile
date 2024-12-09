NAME = philo

SRCS = extra.c philo.c sets.c ph_life.c threads.c obs.c chk.c

OBJ = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread


COLOR_RESET = \033[0m
COLOR_PINK = \033[95m
COLOR_YELLOW = \033[93m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(COLOR_PINK)Build successful$(COLOR_RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "$(COLOR_YELLOW)Objects removed$(COLOR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR_YELLOW)Executable removed$(COLOR_RESET)"

re: fclean all