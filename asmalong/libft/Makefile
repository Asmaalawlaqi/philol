NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = ar -rcs
RM = rm -rf

INCLUDE = .

SRCS = ft_strlen.c ft_strrchr.c ft_strncmp.c ft_strjoin.c  ft_split.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIB) $(NAME) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY = all clean fclean re so_long
